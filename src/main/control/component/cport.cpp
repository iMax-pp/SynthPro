#include "cport.h"

#include "control/cmodule.h"
#include "control/component/cvirtualport.h"
#include "control/component/cwire.h"
#include "control/csynthpro.h"
#include "factory/qtfactory.h"
#include "presentation/component/pport.h"
#include <QGraphicsScene>

CPort::CPort(CVirtualPort* parent, QtFactory* factory)
    : QObject(parent)
    , m_vPort(parent)
    , m_presentation(0)
    , m_factory(factory)
    , m_wire(0)
    , m_tmpWire(0)
    , m_clickableFeedback(0)
    , m_reconnecting(0)
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

void CPort::setWire(CWire* wire)
{
    m_wire = wire;
    QObject::connect(wire, SIGNAL(destroyed()), this, SLOT(wireDeleted()));
}

void CPort::wireDeleted()
{
    m_wire = 0;
}

void CPort::disconnect()
{
    vPort()->disconnect(this);
}

void CPort::reconnect(const QPointF& pos)
{
    CPort* other = m_wire->inPort() == this ? m_wire->outPort() : m_wire->inPort();
    m_reconnecting = other;
    disconnect();
    createTmpWire(other, pos);
}

void CPort::createTmpWire(CPort* from, const QPointF& to)
{
    // Create a temporary wire
    m_tmpWire = m_factory->createWire(presentation()->scene());

    // Don't forget to register ourself as one of the port (the good one of course).
    m_tmpWire->setInPort(from);
    m_tmpWire->showMoveFeedback();
    m_tmpWire->updatePosition(to);

    dynamic_cast<CSynthPro*>(vPort()->module()->synthPro())->showFeedback(from->vPort());
}

void CPort::drag(const QPointF& pos)
{
    if (m_wire) {
        reconnect(pos);
    } else {
        createTmpWire(this, pos);
    }
}

void CPort::dragMove(const QPointF& pos)
{
    if (PPort* pport = dynamic_cast<PPort*>(presentation()->scene()->itemAt(pos))) {
        if (!m_clickableFeedback) {
            m_clickableFeedback = pport;
            if (vPort()->connectable(pport->control()->vPort())) {
                pport->showDropFeedback();
            } else {
                // pport->showUnDropFeedback();
            }
        }
    } else {
        if (m_clickableFeedback) {
            m_clickableFeedback->hideDropFeedback();
            m_clickableFeedback = 0;
        }
    }
    if (m_tmpWire) {
        m_tmpWire->updatePosition(pos);
    }
}

void CPort::drop(CPort* target)
{
    dynamic_cast<CSynthPro*>(vPort()->module()->synthPro())->hideFeedback();
    // Delete the temporary wire
    if (m_tmpWire) {
        delete m_tmpWire;
        m_tmpWire = 0;
    }
    CPort* port = reconnecting() ? m_reconnecting : this;
    // If the user dropped on a target, try to connect to it
    if (target) {
        if (target->m_wire) { // The target port is already connected, first disconnect it
            target->disconnect();
        }
        port->vPort()->connect(target->vPort());
    }
    if (reconnecting()) { // The reconnection is finished, remove the connection ports
        m_reconnecting->vPort()->removeConnectionPort(m_reconnecting);
        vPort()->removeConnectionPort(this);
        m_reconnecting = 0;
    }
}

void CPort::mouseEnter()
{
    presentation()->showClickFeedback();
}

void CPort::mouseLeave()
{
    presentation()->hideClickFeedback();
}

void CPort::showFeedback(bool compatible)
{
    presentation()->showFeedback(compatible);
}

void CPort::hideFeedback()
{
    presentation()->hideFeedback();
}

void CPort::showAvailableFeedback()
{
    presentation()->show();
}


void CPort::hideAvailableFeedback()
{
    presentation()->hide();
}
