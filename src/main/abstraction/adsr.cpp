#include "adsr.h"

#include "abstraction/audiodeviceprovider.h"
#include "abstraction/dimmer.h"
#include "abstraction/inport.h"
#include "abstraction/outport.h"
#include "factory/synthprofactory.h"

ADSR::ADSR(QObject* parent)
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

    m_outPort = factory->createOutPortReplicable(this, "outPort");
    m_outports.append(m_outPort);

    m_attackDimmer = factory->createDimmer("Attack", ATTACK_MIN, ATTACK_MAX, ATTACK_DEFAULT, this);
    m_decayDimmer = factory->createDimmer("Decay", DECAY_MIN, DECAY_MAX, DECAY_DEFAULT, this);
    m_sustainDimmer = factory->createDimmer("Sustain", SUSTAIN_MIN, SUSTAIN_MAX, SUSTAIN_DEFAULT, this);
    m_releaseDimmer = factory->createDimmer("Release", RELEASE_MIN, RELEASE_MAX, RELEASE_DEFAULT, this);

}

void ADSR::ownProcess()
{
    qreal attackInSample = m_attackDimmer->value()*AudioDeviceProvider::OUTPUT_FREQUENCY;
    qreal decayInSample = m_decayDimmer->value()*AudioDeviceProvider::OUTPUT_FREQUENCY;
    qreal releaseInSample = m_releaseDimmer->value()*AudioDeviceProvider::OUTPUT_FREQUENCY;

    qreal currentValue = 0;
    int bufferIndex = 0;

    while (bufferIndex < m_gate->buffer()->length()) {
        currentValue = m_gate->buffer()->data()[bufferIndex];
        if (currentValue > m_gateValue && m_currentState == IDLE) {
            // a gate "on" signal occurs
            m_timeLine = 0;
            m_currentState = ATTACK;
        }

        if (currentValue < m_gateValue) {
            // a gate "of" signal occurs
            m_currentState = RELEASE;
        }
        if (m_currentState == ATTACK && m_timeLine == attackInSample) {
            m_currentState = DECAY;
        }
        if (m_currentState == DECAY && m_timeLine == (attackInSample + decayInSample)) {
            m_currentState = SUSTAIN;
        }
        m_timeLine++;
        bufferIndex++;
        m_gateValue = currentValue;
    }

}
// Todo : calculate of the output buffer is wrong

void ADSR::processADSR()
{
    // these values are not qreals but integers
    qreal attackInSample = m_attackDimmer->value()*AudioDeviceProvider::OUTPUT_FREQUENCY;
    qreal decayInSample = m_decayDimmer->value()*AudioDeviceProvider::OUTPUT_FREQUENCY;
    qreal releaseInSample = m_releaseDimmer->value()*AudioDeviceProvider::OUTPUT_FREQUENCY;
    int bufferIndex = 0;

    // "eat" the values befor upGate
    while (bufferIndex < upGate  && bufferIndex < m_gate->buffer()->length()) {
        bufferIndex++;
    }
    while (m_timeLine < attackInSample && downGate != m_timeLine && upGate != m_timeLine && bufferIndex < m_gate->buffer()->length()) {
        m_outPort->buffer()->data()[bufferIndex] = m_timeLine / attackInSample;
        m_timeLine++;
        bufferIndex++;
    }
    while (m_timeLine < attackInSample + decayInSample && downGate != m_timeLine && upGate != m_timeLine && bufferIndex < m_gate->buffer()->length()) {
        m_outPort->buffer()->data()[bufferIndex] = m_timeLine * (1-m_sustainDimmer->value()) / decayInSample;
        m_timeLine++;
        bufferIndex++;
    }
    while (m_timeLine < downGate && upGate != m_timeLine && bufferIndex < m_gate->buffer()->length()) {
        m_outPort->buffer()->data()[bufferIndex] = m_sustainDimmer->value();
        m_timeLine++;
        bufferIndex++;
    }
    int sustainEnd = m_timeLine;
    while (m_timeLine <= sustainEnd + releaseInSample &&  bufferIndex < m_gate->buffer()->length()) {
        m_outPort->buffer()->data()[bufferIndex] = m_timeLine*m_sustainDimmer->value() / releaseInSample;
        m_timeLine++;
        bufferIndex++;
    }
    // if release is complete, reinitialization of m_timeLine
    if (m_timeLine > sustainEnd + releaseInSample) {
        m_timeLine = 0;
    }
}
