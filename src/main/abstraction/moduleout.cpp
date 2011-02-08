#include "moduleout.h"

#include "audiodeviceprovider.h"
#include "clock.h"
#include "factory/synthprofactory.h"
#include "inport.h"

#include <QDebug>

ModuleOut::ModuleOut(QIODevice* device, QAudioOutput* audioOutput, QObject* parent)
    : Module(parent)
    , m_device(device)
    , m_audioOutput(audioOutput)
{
}

ModuleOut::~ModuleOut()
{
}

void ModuleOut::initialize(SynthProFactory* factory)
{
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
    //qDebug() << "Timer Expired Module Out";



}

void ModuleOut::ownProcess()
{
    // TODO
}
