#include "moduleout.h"

#include "audiodeviceprovider.h"
#include "factory/synthprofactory.h"
#include "inport.h"

ModuleOut::ModuleOut(QIODevice* device, SynthProFactory* factory, QObject* parent)
    : Module(parent)
    , m_device(device)
    , m_factory(factory)
{
}

ModuleOut::~ModuleOut()
{
}

void ModuleOut::initialize()
{
    // Creation of an Input.
    if (m_factory) {
        m_inPort = m_factory->createInPortReplicable(this);
        m_inports.append(m_inPort);
    }
}

void ModuleOut::ownProcess()
{
    // TODO
}
