#include "cvirtualport.h"

#include "control/cinport.h"
#include "control/coutport.h"
#include "control/cportwidget.h"
#include "control/csynthpro.h"
#include "control/cwire.h"
#include "factory/qtfactory.h"
#include "presentation/pvirtualport.h"

CVirtualPort::CVirtualPort(Module* parent, QtFactory* factory, const QString& name, bool replicable, bool gate)
    : VirtualPort(parent, name, replicable, gate)
    , m_presentation(0)
    , m_factory(factory)
{
}

void CVirtualPort::initialize()
{
    // TODO la création des ports widget doit dépendre
    // du nombre de ports répliqués du port virtuel
    // Donc il est possible qu’il soit nécessaire d’affiner
    // la représentation des réplications des ports dans
    // l’abstraction
    replicate();
}

void CVirtualPort::replicate()
{
    CPortWidget* cPortWidget = m_factory->createPortWidget(this, m_factory);
    m_portWidgets.append(cPortWidget);
    presentation()->addReplication(cPortWidget->presentation());
}

void CVirtualPort::setPresentation(PVirtualPort* presentation)
{
    if (m_presentation) {
        delete m_presentation;
        m_presentation = 0;
    }

    m_presentation = presentation;
}

void CVirtualPort::connectTo(VirtualPort* other)
{
    if (connectable(other)) {
        VirtualPort::connectTo(other);
        if (replicable()) {
            CPortWidget* replication = m_factory->createPortWidget(this, m_factory);
            m_portWidgets.append(replication);
            presentation()->addReplication(replication->presentation());
        }
        // That’s ugly, isn’t it?
        if (other->replicable()) {
            CVirtualPort* cOther = dynamic_cast<CVirtualPort*>(other);
            CPortWidget* replication = m_factory->createPortWidget(cOther, m_factory);
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
}

void CVirtualPort::updateWiresPositions()
{
    foreach (CPortWidget* cPortWidget, m_portWidgets) {
        if (cPortWidget->wire()) {
            cPortWidget->wire()->updatePosition();
        }
    }
}

void CVirtualPort::showCompatibleFeedback(CVirtualPort* from)
{
    if (from != this) {
        foreach (CPortWidget* portWidget, m_portWidgets) {
            portWidget->showFeedback(compatible(from));
        }
    }
}

void CVirtualPort::hideFeedback()
{
    foreach (CPortWidget* portWidget, m_portWidgets) {
        portWidget->hideFeedback();
    }
}
