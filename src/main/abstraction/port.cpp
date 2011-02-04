#include "port.h"

#include "abstraction/module.h"

Port::Port(Module* parent, bool replicable, bool gate)
    : QObject(parent)
    , m_module(parent)
    , m_replicable(replicable)
    , m_gate(gate)
{

}

Port::~Port() {}

bool Port::available() const
{
    return m_replicable || m_connections.size() == 0;
}

bool Port::compatible(const Port *other) const
{
     return other->out() != out() && other->gate() == gate();
}

bool Port::connectable(const Port* other) const
{
    return available() && compatible(other);
}

void Port::connectTo(Port* other)
{
    // Add the port to this connections
    m_connections.append(other);

    // Check if this port needs to be added to the other port
    if (!other->m_connections.contains(this)) {
        other->connectTo(this);
        emit connectionsChanged();
    }
}
