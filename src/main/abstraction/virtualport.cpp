#include "virtualport.h"

#include "abstraction/module.h"
#include "abstraction/port.h"
#include "factory/synthprofactory.h"

#include <QDebug>

VirtualPort::VirtualPort(Module* parent, const QString& name, SynthProFactory* factory, bool replicable, bool gate)
    : QObject(parent)
    , m_module(parent)
    , m_name(name)
    , m_replicable(replicable)
    , m_gate(gate)
    , m_factory(factory)
{
}

void VirtualPort::initialize()
{
    replicate(); // Create at least one port
}

VirtualPort::~VirtualPort() { }

Port* VirtualPort::replicate()
{
    Port* port = m_factory->createPort(this);
    connect(port, SIGNAL(connected(Port*, Port*)), this, SLOT(connection(Port*, Port*)));
    connect(port, SIGNAL(disconnected(Port*, Port*)), this, SLOT(disconnection(Port*, Port*)));
    m_connections.append(port);
    return port;
}

bool VirtualPort::available() const
{
    return m_replicable || !m_connections.first()->connection();
}

bool VirtualPort::compatible(const VirtualPort* other) const
{
    return other->out() != out() && other->gate() == gate();
}

bool VirtualPort::connectable(const VirtualPort* other) const
{
    return available() && compatible(other) && other->available();
}

void VirtualPort::connection(Port* own, Port* target)
{
    if (m_connections.last()->connection() && replicable()) {
        replicate();
    }

    if (own->connection() == target && target->connection() == own) { // Emit only once the signal (otherwise it would be emitted by both sides)
        emit connectionsChanged();
    }
}

void VirtualPort::disconnection(Port* own, Port* target)
{
    // Remove the connection
    if (replicable() && m_connections.size() > 0) {
        removePort(own);
    }

    if (!own->connection() && !target->connection()) {
        emit connectionsChanged();
    }
}

bool VirtualPort::removePort(Port* port)
{
    bool result = m_connections.removeOne(port);
    delete port;
    return result;
}
