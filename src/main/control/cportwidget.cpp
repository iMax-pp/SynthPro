#include "cportwidget.h"

#include "control/cport.h"
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

void CPortWidget::drag()
{
    // TODO
    // CWire* wire = m_factory->createWire(presentation()->scene());
    // presentation()->dragWire(wire->presentation());
    if (m_wire) {
        // When starting a new wire, begin by deleting the previous one.
        CPort* other = m_wire->inPort() == this
                       ? dynamic_cast<CPort*>(m_wire->outPort()->port())
                       : dynamic_cast<CPort*>(m_wire->inPort()->port());
        port()->disconnectFrom(other);
        delete m_wire;
    }

    // And create a new one.
    m_wire = m_factory->createWire(presentation()->scene());
    connect(m_wire, SIGNAL(destroyed()), this, SLOT(unsetWire()));

    // Don't forget to register ourself as one of the port (the good one of course).
    if (port()->out()) {
        m_wire->setOutPort(this);
    } else {
        m_wire->setInPort(this);
    }
}

void CPortWidget::dragMove(const QPointF&)
{

}


void CPortWidget::drop(CPortWidget* target)
{
    if (!target || target->port()->out() == port()->out()) {
        // Drop wasn't on a port? or was on a port of the same type? delete wire.
        if (m_wire) {
            delete m_wire;
        }
    } else {
        if (target->port()->out()) {
            // Otherwise connect the other outport with the wire.
            m_wire->setOutPort(target);
        } else {
            // Otherwise connect the other inport with the wire.
            m_wire->setInPort(target);
        }

        target->setWire(m_wire);
        target->port()->connectTo(this->port());

        m_wire->updatePosition();
    }
}
