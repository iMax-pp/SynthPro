#include "modulekeyboard.h"

#include "abstraction/outport.h"
#include "factory/synthprofactory.h"

ModuleKeyboard::ModuleKeyboard(SynthPro* parent)
    : Module(parent)
{
}

ModuleKeyboard::~ModuleKeyboard()
{
}

void ModuleKeyboard::initialize(SynthProFactory* factory)
{
    if (factory) {
        // Creation of the frequency output.
        m_outPortFrequency = factory->createOutPortReplicable(this, "out");
        m_outports.append(m_outPortFrequency);

        // Creation of the gate output.
        m_outPortGate = factory->createOutPortReplicable(this, "gate");
        m_outports.append(m_outPortGate);
    }
}

void ModuleKeyboard::timerExpired()
{

}

void ModuleKeyboard::ownProcess()
{
}
