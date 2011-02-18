#include "cvirtualport.h"

#include "abstraction/component/connection.h"
#include "control/component/cinport.h"
#include "control/component/coutport.h"
#include "control/component/cport.h"
#include "control/component/cwire.h"
#include "control/csynthpro.h"
#include "factory/qtfactory.h"
#include "presentation/component/pport.h"
#include "presentation/component/pwire.h"

#include <QGraphicsScene>

CVirtualPort::CVirtualPort(Module* parent, QtFactory* factory, const QString& name, bool replicable, bool gate)
    : VirtualPort(parent, name, factory, replicable, gate)
    , m_presentation(0)
    , m_factory(factory)
    , m_availablePort(0)
    , m_useOwnPort(0)
    , m_useOthersPort(0)
{
}

CVirtualPort::~CVirtualPort()
{
    if (!m_presentation.isNull()) {
        delete m_presentation;
    }
}

void CVirtualPort::initialize()
{
    m_availablePort = m_factory->createPort(this);
    presentation()->initialize(m_availablePort->presentation());

    updateAvailableFeedback();
}

void CVirtualPort::updateAvailableFeedback()
{
    if (available()) {
        m_availablePort->showAvailableFeedback();
    } else {
        m_availablePort->hideAvailableFeedback();
    }
}

Connection* CVirtualPort::connect(VirtualPort* other)
{
    CVirtualPort* cOther = dynamic_cast<CVirtualPort*>(other);
    Connection* connection = VirtualPort::connect(cOther);

    if (connection) {
        CPort* source = 0;
        CPort* target = 0;
        if (out()) {
            source = m_useOwnPort ? m_useOwnPort : createConnectionPort(connection);
            setConnectionPort(connection, source);
            target = m_useOthersPort ? m_useOthersPort : cOther->createConnectionPort(connection);
            cOther->setConnectionPort(connection, target);
        } else {
            source = m_useOthersPort ? m_useOthersPort : cOther->createConnectionPort(connection);
            cOther->setConnectionPort(connection, source);
            target = m_useOwnPort ? m_useOwnPort : createConnectionPort(connection);
            setConnectionPort(connection, target);
        }

        CWire* wire = m_factory->createWire(presentation()->scene());
        source->setWire(wire);
        target->setWire(wire);
        wire->setOutPort(source);
        wire->setInPort(target);
        wire->updatePosition();
    }

    return connection;
}

Connection* CVirtualPort::connect(CPort* own, CPort* other)
{
    if (own == m_availablePort) {
        // Let the connection create a new CPort
        m_useOwnPort = 0;
    } else {
        // The connection will use the given own port (because it’s actually a *reconnection*)
        m_useOwnPort = own;
    }
    if (other == other->vPort()->m_availablePort) {
        m_useOthersPort = 0;
    } else {
        // Want to connect on an already used target port
        if (!other->reconnecting()) { // The other port may be reconecting if the user drop on the initial port
            // If this port was connected, disconnect it
            other->setReconnecting(true); // Prevent this CPort from deletion
            other->disconnect(); // Perform the disconnection
            other->setReconnecting(false); // Clean-up
        }
        m_useOthersPort = other; // Use the CPort as target port
    }

    // Perform the connection
    Connection* connection = connect(other->vPort());

    m_useOwnPort = 0; // clean-up
    m_useOthersPort = 0; // clean-up

    return connection;
}

CPort* CVirtualPort::createConnectionPort(Connection* connection)
{
    CPort* port = m_factory->createPort(this);
    presentation()->insertConnectionPort(m_connections.indexOf(connection), port->presentation());
    return port;
}

void CVirtualPort::setConnectionPort(Connection* connection, CPort* port)
{
    m_connectedPorts.insert(port, connection);
    updateAvailableFeedback();
}

void CVirtualPort::disconnect(CPort* port)
{
    disconnect(m_connectedPorts.value(port));
}

bool CVirtualPort::disconnect(Connection* connection)
{
    CVirtualPort* other = dynamic_cast<CVirtualPort*>(connection->source()) == this
                          ? dynamic_cast<CVirtualPort*>(connection->target())
                          : dynamic_cast<CVirtualPort*>(connection->source());
    CPort* port = m_connectedPorts.key(connection);
    CPort* othersPort = other->m_connectedPorts.key(connection);
    if (port && othersPort && VirtualPort::disconnect(connection)) {
        port->wire()->deleteLater();
        removeConnectionPortIfNeeded(port);
        other->removeConnectionPortIfNeeded(othersPort);
        return true;
    }
    return false;
}

void CVirtualPort::removeConnectionPortIfNeeded(CPort* port)
{
    if (!port->reconnecting()) {
        removeConnectionPort(port);
    }
}

void CVirtualPort::removeConnectionPort(CPort* port)
{
    m_connectedPorts.remove(port);
    port->deleteLater();
    presentation()->removeConnectionPort(port->presentation());
    updateAvailableFeedback();
}

void CVirtualPort::setPresentation(PVirtualPort* presentation)
{
    if (!m_presentation.isNull()) {
        delete m_presentation;
    }

    m_presentation = presentation;
}

void CVirtualPort::updateWiresPositions()
{
    foreach (CPort* port, m_connectedPorts.keys()) {
        port->wire()->updatePosition();
    }
}

void CVirtualPort::showCompatibleFeedback(CVirtualPort* from)
{
    bool isCompatible = compatible(from);
    if (from != this) {
        m_availablePort->showFeedback(isCompatible);
        foreach (CPort* port, m_connectedPorts.keys()) {
            port->showFeedback(isCompatible);
        }
    }
}

void CVirtualPort::hideFeedback()
{
    m_availablePort->hideFeedback();
    foreach (CPort* port, m_connectedPorts.keys()) {
        port->hideFeedback();
    }
}
