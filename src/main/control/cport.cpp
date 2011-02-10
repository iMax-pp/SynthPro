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
        m_portWidgets.append(m_factory->createPortWidget(this, m_factory));
    }
}

void CPort::disconnectFrom(Port* other)
{
    if (m_connections.contains(other)) {
        Port::disconnectFrom(other);
        // TODO
    }

    dynamic_cast<CSynthPro*>(module()->synthPro())->showFeedback(this);
}

void CPort::updateWiresPositions()
{
    foreach (CPortWidget* cPortWidget, m_portWidgets) {
        if (cPortWidget->wire()) {
            cPortWidget->wire()->updatePosition();
        }
    }

    dynamic_cast<CSynthPro*>(module()->synthPro())->hideFeedback();
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
