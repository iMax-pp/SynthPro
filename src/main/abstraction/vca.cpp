#include "vca.h"

#include "abstraction/dimmer.h"
#include "abstraction/inport.h"
#include "abstraction/outport.h"
#include "factory/synthprofactory.h"

VCA::VCA(QObject* parent)
    :Module(parent)
{
}

void VCA::initialize(SynthProFactory* factory)
{
    m_inPort = factory->createInPortReplicable(this, "in");
    m_inports.append(m_inPort);

    m_outPort = factory->createOutPortReplicable(this, "out");
    m_outports.append(m_outPort);

    m_gainDimmer = factory->createDimmer(GAIN_MIN, GAIN_MAX, GAIN_DEFAULT, this);
}

void VCA::ownProcess()
{
    // ask to the buffer to multiply its value by a coefficient
    m_inPort->buffer()->mul(m_gainDimmer->value());

    // copy the modified input buffer in the ouput buffer
    for (int i = 0;i < m_inPort->buffer()->length();i++) {
        m_outPort->buffer()->data()[i] = m_inPort->buffer()->data()[i];
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
