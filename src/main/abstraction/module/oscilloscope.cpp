#include "oscilloscope.h"

#include "factory/synthprofactory.h"

Oscilloscope::Oscilloscope(SynthPro* parent)
    : Module(parent)
{
}

Oscilloscope::~Oscilloscope()
{
}

void Oscilloscope::initialize(SynthProFactory* factory)
{
    if (factory) {
        // Creation of an Input.
        m_inPort = factory->createInPortReplicable(this, "in");
        m_inports.append(m_inPort);
    }
}

void Oscilloscope::timerExpired()
{

}

void Oscilloscope::ownProcess()
{
}
