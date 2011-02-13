#include "cport.h"

#include "control/cmodule.h"
#include "control/component/cvirtualport.h"
#include "control/component/cwire.h"
#include "control/csynthpro.h"
#include "factory/qtfactory.h"
#include "presentation/component/pport.h"
#include <QGraphicsScene>

CPort::CPort(CVirtualPort* parent, QtFactory* factory)
    : Port(parent)
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

bool CPort::connect(Port* other)
{
    if (Port::connect(other)) {
        CPort* cOther = dynamic_cast<CPort*>(other);
        // Create their wire
        CWire* wire = m_factory->createWire(presentation()->scene()); // HACK way to retrieve the scene, I think
        setWire(wire);
        cOther->setWire(wire);

        if (vPort()->out()) {
            m_wire->setInPort(cOther);
            m_wire->setOutPort(this);
        } else {
            m_wire->setInPort(this);
            m_wire->setOutPort(cOther);
        }
        m_wire->updatePosition();
        return true;
    }
    return false;
}

bool CPort::disconnect()
{
    if (m_wire) {
        delete m_wire;
    }
    return Port::disconnect();
}

void CPort::drag()
{
    if (connected()) {
        // TODO Change this behavior: in this case the current wire should be moved
        // When starting a new wire, begin by deleting the previous one.
        disconnect();
    }

    // Create a temporary wire
    m_tmpWire = m_factory->createWire(presentation()->scene());

    // Don't forget to register ourself as one of the port (the good one of course).
    if (vPort()->out()) {
        m_tmpWire->setOutPort(this);
    } else {
        m_tmpWire->setInPort(this);
    }

    CVirtualPort* cVPort = dynamic_cast<CVirtualPort*>(vPort());
    dynamic_cast<CSynthPro*>(cVPort->module()->synthPro())->showFeedback(cVPort);
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
    if (m_tmpWire) { // This condition should always be true, but I’m a bit defensive today
        delete m_tmpWire;
        m_tmpWire = 0;
    }
    // If the user dropped on a target, try to connect to it
    if (target) {
        connect(target);
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