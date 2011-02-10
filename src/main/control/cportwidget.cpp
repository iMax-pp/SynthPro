#include "cportwidget.h"

#include "control/cmodule.h"
#include "control/cport.h"
#include "control/csynthpro.h"
#include "control/cwire.h"
#include "factory/qtfactory.h"
#include "presentation/portwidget.h"

CPortWidget::CPortWidget(CPort* parent, QtFactory* factory)
    : QObject(parent)
    , m_presentation(0)
    , m_port(parent)
    , m_factory(factory)
    , m_wire(0)
    , m_tmpWire(0)
{
}

void CPortWidget::setPresentation(PortWidget* presentation)
{
    if (m_presentation) {
        delete m_presentation;
        m_presentation = 0;
    }
    m_presentation = presentation;
}


void CPortWidget::setWire(CWire* wire)
{
    if (m_wire) {
        // If we already have a wire, then delete it.
        delete m_wire;
    }

    m_wire = wire;
    // Clean m_wire if the other extremity destroys the wire
    connect(m_wire, SIGNAL(destroyed()), this, SLOT(unsetWire()));
}

void CPortWidget::unsetWire()
{
    m_wire = 0;
}

void CPortWidget::connectTo(CPortWidget* other)
{
    if (port()->connectable(other->port())) {
        // Connect the port to the other
        port()->connectTo(other->port());

        // Create their wire
        m_wire = m_factory->createWire(presentation()->scene()); // HACK way to retrieve the scene, I think
        other->setWire(m_wire);
        // Automatically clear our reference to the wire if the other side deletes the wire
        connect(m_wire, SIGNAL(destroyed()), this, SLOT(unsetWire()));

        if (port()->out()) {
            m_wire->setInPort(other);
            m_wire->setOutPort(this);
        } else {
            m_wire->setInPort(this);
            m_wire->setOutPort(other);
        }
        m_wire->updatePosition();
    }
}

void CPortWidget::disconnectFrom(CPortWidget* other)
{
    port()->disconnectFrom(other->port());
    if (m_wire) {
        delete m_wire;
    }
}

void CPortWidget::drag()
{
    if (m_wire) {
        // TODO Change this behavior: in this case the current wire should be moved
        // When starting a new wire, begin by deleting the previous one.
        CPortWidget* other = m_wire->inPort() == this
                       ? dynamic_cast<CPortWidget*>(m_wire->outPort())
                       : dynamic_cast<CPortWidget*>(m_wire->inPort());
        disconnectFrom(other);
    }

    // Create a temporary wire
    m_tmpWire = m_factory->createWire(presentation()->scene());

    // Don't forget to register ourself as one of the port (the good one of course).
    if (port()->out()) {
        m_tmpWire->setOutPort(this);
    } else {
        m_tmpWire->setInPort(this);
    }

    dynamic_cast<CSynthPro*>(port()->module()->synthPro())->showFeedback(port());
}

void CPortWidget::dragMove(const QPointF& pos)
{
    if (m_tmpWire) {
        m_tmpWire->updatePosition(pos);
    }
}

void CPortWidget::drop(CPortWidget* target)
{
    dynamic_cast<CSynthPro*>(m_port->module()->synthPro())->hideFeedback();
    // Delete the temporary wire
    if (m_tmpWire) { // This condition should always be true, but I’m a bit defensive today
        delete m_tmpWire;
        m_tmpWire = 0;
    }
    // If the user dropped on a target, try to connect to it
    if (target) {
        connectTo(target);
    }
}

void CPortWidget::showFeedback(bool compatible)
{
    m_presentation->showFeedback(compatible);
}

void CPortWidget::hideFeedback()
{
    m_presentation->hideFeedback();
}
