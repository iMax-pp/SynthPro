#include "cvirtualport.h"

#include "control/cinport.h"
#include "control/coutport.h"
#include "control/cport.h"
#include "control/csynthpro.h"
#include "control/cwire.h"
#include "factory/qtfactory.h"
#include "presentation/pvirtualport.h"

CVirtualPort::CVirtualPort(Module* parent, QtFactory* factory, const QString& name, bool replicable, bool gate)
    : VirtualPort(parent, name, factory, replicable, gate)
    , m_presentation(0)
    , m_factory(factory)
{
}

Port* CVirtualPort::replicate()
{
    CPort* cPort = dynamic_cast<CPort*>(VirtualPort::replicate());
    presentation()->addReplication(cPort->presentation());
    return cPort;
}

void CVirtualPort::setPresentation(PVirtualPort* presentation)
{
    if (m_presentation) {
        delete m_presentation;
        m_presentation = 0;
    }

    m_presentation = presentation;
}

/*void CVirtualPort::connectTo(VirtualPort* other)
{
    if (connectable(other)) {
        VirtualPort::connectTo(other);
        if (replicable()) {
            CPort* replication = m_factory->createPortWidget(this, m_factory);
            m_portWidgets.append(replication);
            presentation()->addReplication(replication->presentation());
        }
        // That’s ugly, isn’t it?
        if (other->replicable()) {
            CVirtualPort* cOther = dynamic_cast<CVirtualPort*>(other);
            CPort* replication = m_factory->createPortWidget(cOther, m_factory);
            cOther->m_portWidgets.append(replication);
            cOther->presentation()->addReplication(replication->presentation());
        }
    }
}

void CVirtualPort::disconnectFrom(VirtualPort* other)
{
    if (m_connections.contains(other)) {
        VirtualPort::disconnectFrom(other);
    }
}*/

void CVirtualPort::updateWiresPositions()
{
    foreach (Port* port, connections()) {
        CPort* cPort = dynamic_cast<CPort*>(port);
        if (cPort->wire()) {
            cPort->wire()->updatePosition();
        }
    }
}

void CVirtualPort::showCompatibleFeedback(CVirtualPort* from)
{
    if (from != this) {
        foreach (Port* port, connections()) {
            CPort* cPort = dynamic_cast<CPort*>(port);
            cPort->showFeedback(compatible(from));
        }
    }
}

void CVirtualPort::hideFeedback()
{
    foreach (Port* port, connections()) {
        CPort* cPort = dynamic_cast<CPort*>(port);
        cPort->hideFeedback();
    }
}
