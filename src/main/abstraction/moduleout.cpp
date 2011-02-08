#include "moduleout.h"

#include "audiodeviceprovider.h"
#include "clock.h"
#include "factory/synthprofactory.h"
#include "inport.h"

#include <QDebug>

ModuleOut::ModuleOut(QIODevice* device, QObject* parent)
    : Module(parent)
    , m_device(device)
{
}

ModuleOut::~ModuleOut()
{
}

void ModuleOut::initialize(SynthProFactory* factory)
{
            qDebug() << "****** INIT ModuleOut *****";
    if (factory) {
        // Creation of an Input.
        m_inPort = factory->createInPortReplicable(this);
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
