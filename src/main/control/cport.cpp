#include "cport.h"

#include "control/cinport.h"
#include "control/coutport.h"
#include "control/cportwidget.h"
#include "control/csynthpro.h"
#include "control/cwire.h"
#include "factory/qtfactory.h"

CPort::CPort(Module* parent, QtFactory* factory, const QString& name, bool replicable, bool gate)
    : Port(parent, name, replicable, gate)
    , m_presentation(0)
    , m_factory(factory)
{
}

void CPort::initialize()
{
    // TODO la création des ports widget doit dépendre
    // du nombre de ports répliqués du port virtuel
    // Donc il est possible qu’il soit nécessaire d’affiner
    // la représentation des réplications des ports dans
    // l’abstraction
    replicate();
}

void CPort::replicate()
{
    CPortWidget* cPortWidget = m_factory->createPortWidget(this, m_factory);
    m_portWidgets.append(cPortWidget);
    presentation()->addReplication(cPortWidget->presentation());
}

void CPort::setPresentation(PPort* presentation)
{
    if (m_presentation) {
        delete m_presentation;
        m_presentation = 0;
    }

    m_presentation = presentation;
}

void CPort::connectTo(Port* other)
{
    if (connectable(other)) {
        Port::connectTo(other);
        if (replicable()) {
            CPortWidget* replication = m_factory->createPortWidget(this, m_factory);
            m_portWidgets.append(replication);
            presentation()->addReplication(replication->presentation());
        }
    }
}

void CPort::disconnectFrom(Port* other)
{
    if (m_connections.contains(other)) {
        Port::disconnectFrom(other);
    }
}

void CPort::updateWiresPositions()
{
    foreach (CPortWidget* cPortWidget, m_portWidgets) {
        if (cPortWidget->wire()) {
            cPortWidget->wire()->updatePosition();
        }
    }
}

void CPort::showFeedback(CPort* from)
{
    if (from != this) {
        foreach (CPortWidget* portWidget, m_portWidgets) {
            portWidget->showFeedback(compatible(from));
        }
    }
}

void CPort::hideFeedback()
{
    foreach (CPortWidget* portWidget, m_portWidgets) {
        portWidget->hideFeedback();
    }
}
