#include "virtualport.h"

#include "abstraction/module.h"

VirtualPort::VirtualPort(Module* parent, const QString& name, bool replicable, bool gate)
    : QObject(parent)
    , m_module(parent)
    , m_name(name)
    , m_replicable(replicable)
    , m_gate(gate)
{
}

VirtualPort::~VirtualPort() { }

bool VirtualPort::available() const
{
    return m_replicable || m_connections.size() == 0;
}

bool VirtualPort::compatible(const VirtualPort* other) const
{
    return other->out() != out() && other->gate() == gate();
}

bool VirtualPort::connectable(const VirtualPort* other) const
{
    return available() && compatible(other) && other->available();
}

void VirtualPort::connectTo(VirtualPort* other)
{
    if (connectable(other)) {
        m_connections.append(other);
        other->m_connections.append(this);
        qDebug(QString("VirtualPort::connectTo() %1 -> %2").arg(name()).arg(other->name()).toLatin1());
        emit connectionsChanged();
    }
}

void VirtualPort::disconnectFrom(VirtualPort* other)
{
    if (m_connections.contains(other)) {
        qDebug(QString("VirtualPort::disconnectFrom() %1 - %2").arg(name()).arg(other->name()).toLatin1());
        m_connections.removeOne(other);
        other->m_connections.removeOne(this);
        emit connectionsChanged();
    }
}
