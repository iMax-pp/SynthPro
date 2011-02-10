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
        port()->connectTo(other->port());
        CWire* wire = m_factory->createWire(presentation()->scene()); // HACK way to retrieve the scene, I think
        if (port()->out()) {
            wire->setInPort(other);
            wire->setOutPort(this);
        } else {
            wire->setInPort(this);
            wire->setOutPort(other);
        }
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
        CPort* other = m_wire->inPort() == this
                       ? dynamic_cast<CPort*>(m_wire->outPort()->port())
                       : dynamic_cast<CPort*>(m_wire->inPort()->port());
        port()->disconnectFrom(other);
        delete m_wire;
    }

    // And create a new one.
    m_wire = m_factory->createWire(presentation()->scene());
    // Automatically clear our reference to the wire if the other side deletes the wire
    connect(wire(), SIGNAL(destroyed()), this, SLOT(unsetWire()));

    // Don't forget to register ourself as one of the port (the good one of course).
    if (port()->out()) {
        wire()->setOutPort(this);
    } else {
        wire()->setInPort(this);
    }

    dynamic_cast<CSynthPro*>(port()->module()->synthPro())->showFeedback(port());
}

void CPortWidget::dragMove(const QPointF& pos)
{
    wire()->updatePosition(pos);
}

void CPortWidget::drop(CPortWidget* target)
{
    dynamic_cast<CSynthPro*>(m_port->module()->synthPro())->hideFeedback();
    // Delete the temporary wire
    if (m_wire) {
        delete m_wire;
    }
    // If the user dropped on a target, try to connect to it
    if (target) {
        target->port()->connectTo(this->port());
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
