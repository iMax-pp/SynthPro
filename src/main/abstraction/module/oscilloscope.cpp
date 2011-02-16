#include "oscilloscope.h"

#include "abstraction/component/pushbutton.h"
#include "factory/synthprofactory.h"

Oscilloscope::Oscilloscope(SynthPro* parent)
    : Module(parent)
    , m_stabilized(false)
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

        m_stabilizeControl = factory->createPushButton("Stabilize", this);

        connect(m_stabilizeControl, SIGNAL(buttonPushed()), this, SLOT(stabilizedPushed()));
    }
}

void Oscilloscope::timerExpired()
{
}

void Oscilloscope::ownProcess()
{
}

bool Oscilloscope::stabilized()
{
    return m_stabilized;
}

void Oscilloscope::stabilizedPushed()
{
    m_stabilized = !m_stabilized;
}
