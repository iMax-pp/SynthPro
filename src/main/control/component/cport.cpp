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

void CPort::drag(const QPointF& pos)
{
    if (m_wire) {
        // TODO reconnect the current wire
        return;
    }

    // Create a temporary wire
    m_tmpWire = m_factory->createWire(presentation()->scene());

    // Don't forget to register ourself as one of the port (the good one of course).
    if (vPort()->out()) {
        m_tmpWire->setOutPort(this);
    } else {
        m_tmpWire->setInPort(this);
    }
    m_tmpWire->updatePosition(pos);

    dynamic_cast<CSynthPro*>(vPort()->module()->synthPro())->showFeedback(vPort());
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
    // If the user dropped on a target, try to connect to it
    if (target) {
        if (m_wire) { // This port is already connected, let’s reconnect it
            // TODO
        } else {
            vPort()->connect(target->vPort());
        }
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
