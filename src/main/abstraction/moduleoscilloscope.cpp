#include "moduleoscilloscope.h"

#include "factory/synthprofactory.h"

ModuleOscilloscope::ModuleOscilloscope(SynthPro* parent)
    : Module(parent)
{
}

ModuleOscilloscope::~ModuleOscilloscope()
{
}

void ModuleOscilloscope::initialize(SynthProFactory* factory)
{
    if (factory) {
        // Creation of an Input.
        m_inPort = factory->createInPortReplicable(this, "in");
        m_inports.append(m_inPort);
    }
}

void ModuleOscilloscope::timerExpired()
{

}

void ModuleOscilloscope::ownProcess()
{
}
