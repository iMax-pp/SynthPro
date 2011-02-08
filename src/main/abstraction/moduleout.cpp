#include "moduleout.h"

#include "audiodeviceprovider.h"
#include "clock.h"
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
    if (m_factory) {
        // Creation of an Input.
        m_inPort = m_factory->createInPortReplicable(this);
        m_inports.append(m_inPort);

        Clock& clock = Clock::instance();
        clock.registerFastClock(this);
    }
}

void ModuleOut::timerExpired()
{
    // TODO
}

void ModuleOut::ownProcess()
{
    // TODO
}
