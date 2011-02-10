#include "adsr.h"

#include "abstraction/audiodeviceprovider.h"
#include "abstraction/dimmer.h"
#include "abstraction/inport.h"
#include "abstraction/outport.h"
#include "factory/synthprofactory.h"

ADSR::ADSR(QObject* parent)
    : Module(parent)
    , m_timeLine(0)
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
    qreal oldValue =  m_gate->buffer()->data()[0];
    qreal currentValue = 0;
    int upGate = 0;
    int downGate = 0;

    // gate buffer analysis searching an start or a stop signal. I'm really not sure of the efficiency of this method
    for (int i = 1; i < m_gate->buffer()->length(); i += 10) {
        currentValue = m_gate->buffer()->data()[i];
        if (currentValue-oldValue > GATE_LEVEL) {
            upGate = i;
        }
        if (currentValue-oldValue < 1-GATE_LEVEL) {
            downGate = i;
        }

    }
    // if there is a upGate in the the buffer or if an ADSR cycle is begin we treat the buffer, else there is nothing to do
    if (upGate != 0 || m_timeLine != 0) {
        processADSR(upGate, downGate);
    }
}

// Todo : calculate of the output buffer is wrong

void ADSR::processADSR(int upGate, int downGate)
{
    // these values are not qreals but integers
    int attackInSample = m_attackDimmer->value()*AudioDeviceProvider::OUTPUT_FREQUENCY;
    int decayInSample = m_decayDimmer->value()*AudioDeviceProvider::OUTPUT_FREQUENCY;
    int releaseInSample = m_releaseDimmer->value()*AudioDeviceProvider::OUTPUT_FREQUENCY;
    int bufferIndex = 0;

    // "eat" the values before upGate
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
