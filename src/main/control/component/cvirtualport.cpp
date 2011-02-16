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
    }
    return connection;
}

CPort* CVirtualPort::createConnectionPort(Connection* connection)
{
    CPort* port = m_factory->createPort(this);
    m_connectedPorts.insert(port, connection);
    presentation()->insertConnectionPort(m_connections.indexOf(connection), port->presentation());
    updateAvailableFeedback();
    return port;
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
        if (!port->reconnecting()) {
            deleteConnectionPort(port);
            other->deleteConnectionPort(othersPort);
        }
        return true;
    }
    return false;
}

void CVirtualPort::deleteConnectionPort(CPort* port)
{
    removeConnectionPort(port);
    port->deleteLater();
}

void CVirtualPort::removeConnectionPort(CPort* port)
{
    presentation()->removeConnectionPort(port->presentation());
    m_connectedPorts.remove(port);
    updateAvailableFeedback();
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
