#include "module.h"

#include "abstraction/inport.h"
#include "abstraction/outport.h"
#include "abstraction/synthpro.h"

Module::Module(SynthPro* parent)
    : QObject(parent)
{
}

Module::~Module()
{
}

const QList<Module*> Module::requirements() const
{
    m_requirements.clear();

    foreach (InPort* port, inports()) {
        foreach (Port* connected, port->connections()) {
            m_requirements.append(connected->module());
        }
    }

    return m_requirements;
}

SynthPro* Module::synthPro() const
{
    dynamic_cast<SynthPro*>(parent());
}

void Module::process()
{
    fetchInput();
    ownProcess();
}

void Module::fetchInput()
{
    foreach (InPort* input, m_inports) {
        input->fetch();
    }
}

void Module::timerExpired()
{
}
