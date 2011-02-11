#include "module.h"

#include "abstraction/inport.h"
#include "abstraction/outport.h"
#include "abstraction/port.h"
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

    foreach (InPort* in, inports()) {
        foreach (Port* port, in->connections()) {
            if (port->connection())
            m_requirements.append(port->connection()->vPort()->module());
        }
    }

    return m_requirements;
}

SynthPro* Module::synthPro() const
{
    return dynamic_cast<SynthPro*>(parent());
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
