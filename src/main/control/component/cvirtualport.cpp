#include "cvirtualport.h"

#include "abstraction/component/connection.h"
#include "control/component/cinport.h"
#include "control/component/coutport.h"
#include "control/component/cport.h"
#include "control/component/cwire.h"
#include "control/csynthpro.h"
#include "factory/qtfactory.h"
#include "presentation/component/pport.h"
#include "presentation/component/pvirtualport.h"
#include "presentation/component/pwire.h"

#include <QGraphicsScene>

CVirtualPort::CVirtualPort(Module* parent, QtFactory* factory, const QString& name, bool replicable, bool gate)
    : VirtualPort(parent, name, factory, replicable, gate)
    , m_presentation(0)
    , m_factory(factory)
    , m_availablePort(0)
{
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
            source = createConnectionPort(connection);
            target = cOther->createConnectionPort(connection);
        } else {
            source = cOther->createConnectionPort(connection);
            target = createConnectionPort(connection);
        }
        CWire* wire = m_factory->createWire(presentation()->scene());
        source->setWire(wire);
        target->setWire(wire);
        wire->setOutPort(source);
        wire->setInPort(target);
        wire->updatePosition();
        updateAvailableFeedback();
    }
    return connection;
}

CPort* CVirtualPort::createConnectionPort(Connection* connection)
{
    int idx = m_connections.indexOf(connection);
    CPort* port = m_factory->createPort(this);
    presentation()->addConnectionPort(port->presentation());
    m_connectedPorts.insert(idx, port);
    return port;
}

void CVirtualPort::disconnect(CPort* port)
{
    disconnect(port2Connection(port));
}

bool CVirtualPort::disconnect(Connection* connection)
{
    CVirtualPort* other = dynamic_cast<CVirtualPort*>(connection->source()) == this
                          ? dynamic_cast<CVirtualPort*>(connection->target())
                          : dynamic_cast<CVirtualPort*>(connection->source());
    int idx = m_connections.indexOf(connection);
    if (VirtualPort::disconnect(connection)) {
        CPort* port = m_connectedPorts.at(idx);
        m_connectedPorts.value(idx)->wire()->deleteLater();
        if (!port->reconnecting()) {
            deleteConnectionPort(idx);
            other->deleteConnectionPort(idx);
        }
        return true;
    }
    return false;
}

void CVirtualPort::deleteConnectionPort(int idx)
{
    CPort* port = m_connectedPorts.at(idx);
    removeConnectionPort(port);
    port->deleteLater();
}

void CVirtualPort::removeConnectionPort(CPort* port)
{
    presentation()->removeConnectionPort(port->presentation());
    m_connectedPorts.removeOne(port);
}

CPort* CVirtualPort::connection2Port(Connection* connection) const
{
    int i = m_connections.indexOf(connection);
    if (i >= 0) {
        return m_connectedPorts.at(i);
    }
    return 0;
}

Connection* CVirtualPort::port2Connection(CPort* port) const
{
    int i = m_connectedPorts.indexOf(port);
    if (i >= 0) {
        return m_connections.at(i);
    }
    return 0;
}


void CVirtualPort::setPresentation(PVirtualPort* presentation)
{
    if (m_presentation) {
        delete m_presentation;
        m_presentation = 0;
    }

    m_presentation = presentation;
}

void CVirtualPort::updateWiresPositions()
{
    foreach (CPort* port, m_connectedPorts) {
        port->wire()->updatePosition();
    }
}

void CVirtualPort::showCompatibleFeedback(CVirtualPort* from)
{
    bool isCompatible = compatible(from);
    if (from != this) {
        m_availablePort->showFeedback(isCompatible);
        foreach (CPort* port, m_connectedPorts) {
            port->showFeedback(isCompatible);
        }
    }
}

void CVirtualPort::hideFeedback()
{
    m_availablePort->hideFeedback();
    foreach (CPort* port, m_connectedPorts) {
        port->hideFeedback();
    }
}
