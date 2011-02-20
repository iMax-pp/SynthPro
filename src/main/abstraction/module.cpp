#include "module.h"

#include "abstraction/component/connection.h"
#include "abstraction/component/inport.h"
#include "abstraction/component/outport.h"
#include "abstraction/synthpro.h"

Module::Module(SynthPro* parent)
    : QObject(parent)
{
}

Module::~Module()
{
}

void Module::prepareDestruction()
{
    foreach (InPort* port, m_inports) {
        while (port->connections().size() > 0) {
            port->disconnect(port->connections().first());
        }
    }
    foreach (OutPort* port, m_outports) {
        while (port->connections().size() > 0) {
            port->disconnect(port->connections().first());
        }
    }
}

const QList<Module*> Module::requirements() const
{
    m_requirements.clear();

    foreach (InPort* in, inports()) {
        foreach (Connection* connection, in->connections()) {
            m_requirements.append(connection->source()->module());
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
