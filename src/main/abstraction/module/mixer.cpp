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

void Mixer::initialize(SynthProFactory * factory)
{
    m_MixInPorts = new QMap<InPort*, Dimmer*>();
    for (int i = 0 ; i < MIXER_SIZE ; i++) {
        InPort* in =  factory->createInPortReplicable(this, "in" + i);
        m_inports.append(in);
        m_MixInPorts->insert(in, factory->createDimmer("dimmer" + i, 0, 5, 2.5, this));

    }

}

void Mixer::ownProcess()
{
    Buffer buffer = Buffer();

    QMap<InPort*, Dimmer*>::iterator ite;
    for (ite = m_MixInPorts->begin(); ite != m_MixInPorts->end(); ++ite) {
        qDebug() << ite.key()->connections().size();
    }
}
