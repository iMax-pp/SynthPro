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
    m_input1 = factory->createInPortReplicable(this, "input1");
    m_inports.append(m_input1);

    m_output1 = factory->createOutPortReplicable(this, "output1");
    m_outports.append(m_output1);

    m_gain = factory->createDimmer(GAIN_MIN, GAIN_MAX, GAIN_DEFAULT, this);
}

void VCA::ownProcess()
{
    qDebug() << "ownProcess";
    m_input1->buffer()->mul(m_gain->value());
    for (int i = 0;i < m_input1->buffer()->length();i++) {
        qDebug() << "boucle";
        m_output1->buffer()->data()[i] = m_input1->buffer()->data()[i];
    }
}

qreal VCA::gain()
{
    return m_gain->value();
}

void VCA::setGain(qreal gain)
{
    m_gain->setValue(gain);
}
