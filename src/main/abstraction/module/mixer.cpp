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
    m_outPort = factory->createOutPortReplicable(this, "out");
    m_outports.append(m_outPort);

    m_mixInPorts = new QMap<InPort*, Dimmer*>();

    for (int i = 0 ; i < MIXER_SIZE ; i++) {
        InPort* in =  factory->createInPort(this, "in" + QString::number(i));
        m_inports.append(in);
        m_mixInPorts->insert(in, factory->createSliderDimmer("dimmer" + QString::number(i),
                                                             0, 5, 2.5, this));
    }
}

void Mixer::ownProcess()
{
    Buffer buffer = Buffer();
    int nbPortConnected = 0;

    for (int j = 0 ; j < inports().size() ;  j++) {
        if (inports().at(j)->connections().size() != 0)  {
            nbPortConnected++;
            for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; i++) {
                buffer.data()[i] += inports().at(j)->buffer()->data()[i];
            }
        }
    }
    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; i++) {
        buffer.data()[i] /= nbPortConnected;
        m_outPort->buffer()->data()[i] = buffer.data()[i];
    }
}
