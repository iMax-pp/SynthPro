#include "virtualport.h"

#include "abstraction/component/connection.h"
#include "abstraction/component/inport.h"
#include "abstraction/component/outport.h"
#include "abstraction/module.h"
#include "factory/synthprofactory.h"

VirtualPort::VirtualPort(Module* parent, const QString& name, SynthProFactory* factory, bool replicable, bool gate)
    : QObject(parent)
    , m_module(parent)
    , m_name(name)
    , m_replicable(replicable)
    , m_gate(gate)
    , m_factory(factory)
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
    return available() && other->out() != out() && other->available();
}

Connection* VirtualPort::connect(VirtualPort* other)
{
    Connection* connection = 0;
    if (connectable(other)) {
        // We don’t need to manually add the connection to our m_connections list because it automatically adds itself on creation
        if (out()) {
            connection = m_factory->createConnection(dynamic_cast<OutPort*>(this), dynamic_cast<InPort*>(other));
        } else {
            connection = m_factory->createConnection(dynamic_cast<OutPort*>(other), dynamic_cast<InPort*>(this));
        }
        emit connectionsChanged();
    }
    return connection;
}

bool VirtualPort::disconnect(Connection* connection)
{
    if (m_connections.contains(connection)) {
        // We don’t need to manually remove the connection from our m_connections list because it automatically removes itself on destruction
        delete connection;
        emit connectionsChanged();
        return true;
    }
    return false;
}

void VirtualPort::addConnection(Connection* connection)
{
    m_connections.append(connection);
}

void VirtualPort::removeConnection(Connection* connection)
{
    m_connections.removeOne(connection);
}
