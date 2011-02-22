#include "vca.h"

#include "abstraction/component/dimmer.h"
#include "abstraction/component/inport.h"
#include "abstraction/component/outport.h"
#include "factory/synthprofactory.h"

VCA::VCA(SynthPro* parent)
    : Module(parent)
    , m_inPort(0)
    , m_controlInput(0)
    , m_outPort(0)
    , m_gainDimmer(0)
{
}

void VCA::initialize(SynthProFactory* factory)
{
    m_inPort = factory->createInPortReplicable(this, tr("in"));
    m_inports.append(m_inPort);

    m_controlInput = factory->createInPort(this, tr("control"));
    m_inports.append(m_controlInput);

    m_outPort = factory->createOutPortReplicable(this, tr("out"));
    m_outports.append(m_outPort);

    m_gainDimmer = factory->createDialDimmer(tr("Gain"), GAIN_MIN, GAIN_MAX, GAIN_DEFAULT, this);
}

void VCA::ownProcess()
{
    /*if (!m_controlInput->available()) {
        for (int i = 0; i < m_controlInput->buffer()->length(); i++) {
            m_inPort->buffer()->data()[i] = m_inPort->buffer()->data()[i] * m_controlInput->buffer()->data()[i];
        }
    }

    // ask to the buffer to multiply its value by a coefficient
    m_inPort->buffer()->mul(m_gainDimmer->value());

    // copy the modified input buffer in the ouput buffer
    for (int i = 0; i < m_inPort->buffer()->length(); i++) {
        m_outPort->buffer()->data()[i] = m_inPort->buffer()->data()[i];
    }*/
    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; i++) {
        m_outPort->buffer()->data()[i] =
                (m_controlInput->buffer()->data()[i] + m_gainDimmer->value())*m_inPort->buffer()->data()[i];
    }




}

qreal VCA::gain()
{
    return m_gainDimmer->value();
}

void VCA::setGain(qreal gain)
{
    m_gainDimmer->setValue(gain);
}
