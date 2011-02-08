#include "port.h"

#include "abstraction/module.h"

Port::Port(Module* parent, const QString& name, bool replicable, bool gate)
    : QObject(parent)
    , m_module(parent)
    , m_name(name)
    , m_replicable(replicable)
    , m_gate(gate)
{
}

Port::~Port() { }

bool Port::available() const
{
    return m_replicable || m_connections.size() == 0;
}

bool Port::compatible(const Port* other) const
{
    return other->out() != out() && other->gate() == gate();
}

bool Port::connectable(const Port* other) const
{
    return available() && compatible(other) && other->available();
}

void Port::connectTo(Port* other)
{
    if (connectable(other)) {
        m_connections.append(other);
        other->m_connections.append(this);
        emit connectionsChanged();
    }
}

void Port::disconnectFrom(Port* other)
{
    if (m_connections.contains(other)) {
        m_connections.removeOne(other);
        other->m_connections.removeOne(this);
        emit connectionsChanged();
    }
}
