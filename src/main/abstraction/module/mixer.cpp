#include "mixer.h"

#include "abstraction/buffer.h"
#include "abstraction/component/dimmer.h"
#include "abstraction/component/inport.h"
#include "abstraction/component/outport.h"
#include "factory/synthprofactory.h"

#include <QDebug>

Mixer::Mixer(SynthPro* parent)
    : Module(parent)
{
}

Mixer::~Mixer()
{
}

void Mixer::initialize(SynthProFactory* factory)
{
    m_mixInPorts = new QMap<InPort*, Dimmer*>();
    for (int i = 0 ; i < MIXER_SIZE ; i++) {
        InPort* in =  factory->createInPortReplicable(this, "in" + QString::number(i));
        m_inports.append(in);
        m_mixInPorts->insert(in, factory->createDimmer("dimmer" + QString::number(i),
                                                       0, 5, 2.5, this));
    }

    m_outPort = factory->createOutPortReplicable(this, "out");
}

void Mixer::ownProcess()
{
    Buffer buffer = Buffer();

    QMap<InPort*, Dimmer*>::iterator ite;
    for (ite = m_mixInPorts->begin(); ite != m_mixInPorts->end(); ++ite) {
        qDebug() << ite.key()->connections().size();
    }
}
