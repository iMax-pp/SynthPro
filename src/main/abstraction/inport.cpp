#include "inport.h"

#include "abstraction/buffer.h"
#include "abstraction/port.h"

InPort::InPort(Module* parent, const QString& name, SynthProFactory* factory, bool replicable, bool gate)
    : VirtualPort(parent, name, factory, replicable, gate)
{
}

void InPort::fetch()
{
    m_buffer.clear();

    for (int i = 0; i < m_buffer.length(); i++) {
        foreach (Port* port, connections()) {
            if (port->connection()) {
                m_buffer.data()[i] += port->connection()->vPort()->buffer()->data()[i];
            }
        }
    }
}
