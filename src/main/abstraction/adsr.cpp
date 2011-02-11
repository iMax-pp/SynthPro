#include "adsr.h"

#include "abstraction/audiodeviceprovider.h"
#include "abstraction/dimmer.h"
#include "abstraction/inport.h"
#include "abstraction/outport.h"
#include "abstraction/pushbutton.h"
#include "factory/synthprofactory.h"

#include <QDebug>

ADSR::ADSR(SynthPro* parent)
    : Module(parent)
    , m_timeLine(0)
    , m_currentState(IDLE)
    , m_gateValue(0)
{
}

void ADSR::initialize(SynthProFactory* factory)
{
    m_gate = factory->createInPortGate(this, "gate");
    m_inports.append(m_gate);

    m_outPort = factory->createOutPortReplicable(this, "out");
    m_outports.append(m_outPort);

    m_attackDimmer = factory->createDimmer("Attack", ATTACK_MIN, ATTACK_MAX, ATTACK_DEFAULT, this);
    m_decayDimmer = factory->createDimmer("Decay", DECAY_MIN, DECAY_MAX, DECAY_DEFAULT, this);
    m_sustainDimmer = factory->createDimmer("Sustain", SUSTAIN_MIN, SUSTAIN_MAX, SUSTAIN_DEFAULT, this);
    m_releaseDimmer = factory->createDimmer("Release", RELEASE_MIN, RELEASE_MAX, RELEASE_DEFAULT, this);

    m_manualControl = factory->createPushButton("Manual", this);
}

void ADSR::ownProcess()
{
    int attackInSample = m_attackDimmer->value()*AudioDeviceProvider::OUTPUT_FREQUENCY;
    int decayInSample = m_decayDimmer->value()*AudioDeviceProvider::OUTPUT_FREQUENCY;
    int releaseInSample = m_releaseDimmer->value()*AudioDeviceProvider::OUTPUT_FREQUENCY;

    int bufferIndex = 0;
    qreal currentValue = m_manualControl->pushed() ? 1 : 0;
    qreal startRelease = 0;

    while (bufferIndex < m_gate->buffer()->length()) {
        if (currentValue == 0) {
            currentValue = m_gate->buffer()->data()[bufferIndex];
        }

        if (currentValue > m_gateValue && m_currentState == IDLE) {
            // a gate "on" signal occurs
            m_timeLine = 0;
            m_currentState = ATTACK;
        }

        if (currentValue < m_gateValue) {
            // a gate "of" signal occurs
            m_currentState = RELEASE;
            startRelease = m_timeLine;
        }
        if (m_currentState == ATTACK && m_timeLine == attackInSample) {
            m_currentState = DECAY;
        }
        if (m_currentState == DECAY && m_timeLine == (attackInSample + decayInSample)) {
            m_currentState = SUSTAIN;
        }
        if (m_currentState == RELEASE &&  m_timeLine == startRelease + releaseInSample) {
            m_currentState = IDLE;
        }
        switch (m_currentState) {
        case ATTACK :
            if (m_attackDimmer->value() != 0) {
                outports().first()->buffer()->data()[bufferIndex] = (qreal)m_timeLine / (qreal)attackInSample;
            } else {
                outports().first()->buffer()->data()[bufferIndex] = 1;
            }
            break;
        case DECAY :
            if (m_decayDimmer->value() != 0) {
                qreal attack = attackInSample;
                qreal decay = decayInSample;
                qreal sustain = m_sustainDimmer->value();
                outports().first()->buffer()->data()[bufferIndex] = m_timeLine*((sustain-1) / (decay)) + (1 + attack*(1-sustain) / decay);
            } else {
                outports().first()->buffer()->data()[bufferIndex] = m_sustainDimmer->value();
            }
            break;
        case SUSTAIN :
            outports().first()->buffer()->data()[bufferIndex] = m_sustainDimmer->value();
            break;
        case RELEASE :
            if (m_decayDimmer->value() != 0) {
                outports().first()->buffer()->data()[bufferIndex] =
                        m_sustainDimmer->value() - m_sustainDimmer->value()*(m_timeLine-startRelease) / releaseInSample;
            } else {
                outports().first()->buffer()->data()[bufferIndex] = 0;
            }
            break;
        case IDLE :
            break;
        }

        if (m_currentState != IDLE) {
            m_timeLine++;
        }

        bufferIndex++;
        m_gateValue = currentValue;
    }

}

void ADSR::setAttackValue(qreal value)
{
    m_attackDimmer->setValue(value);
}

void ADSR::setDecayValue(qreal value)
{
    m_decayDimmer->setValue(value);
}

void ADSR::setSustainValue(qreal value)
{
    m_sustainDimmer->setValue(value);
}

void ADSR::setReleaseValue(qreal value)
{
    m_releaseDimmer->setValue(value);
}
