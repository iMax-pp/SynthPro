#include "cport.h"

#include "cinport.h"
#include "coutport.h"
#include "cwire.h"
#include "factory/synthprofactory.h"

CPort::CPort(Module* parent, SynthProFactory* factory, const QString& name, bool replicable, bool gate)
    : Port(parent, name, replicable, gate)
    , m_presentation(0)
    , m_wire(0)
    , m_factory(factory)
{
}

CPort::~CPort()
{
    /* We guess that this port presentation is owned by
     * a Module’s presentation, so it will be deleted
     * automatically (actually if we uncomment the
     * following lines the program crashes)
    if (m_presentation) {
        delete m_presentation;
    }*/
}

void CPort::setPresentation(PPort* presentation)
{
    if (m_presentation) {
        delete m_presentation;
    }

    m_presentation = presentation;
}

PPort* CPort::presentation() const
{
    return m_presentation;
}

CWire* CPort::wire() const
{
    return m_wire;
}

void CPort::setWire(CWire* wire)
{
    if (wire && m_wire) {
        // If we are not trying to unset the wire and if we have a wire, then delete it.
        delete m_wire;
    }

    m_wire = wire;
}

void CPort::startWire()
{
    if (m_wire) {
        // When starting a new wire, begin by deleting the previous one.
        CPort* other = m_wire->inPort() == this
                       ? dynamic_cast<CPort*>(m_wire->outPort())
                       : dynamic_cast<CPort*>(m_wire->inPort());
        disconnectFrom(other);
        delete m_wire;
    }

    // And create a new one.
    m_wire = m_factory->createWire(m_presentation->scene());

    // Don't forget to register ourself as one of the port (the good one of course).
    if (out()) {
        m_wire->setOutPort(dynamic_cast<COutPort*>(this));
    } else {
        m_wire->setInPort(dynamic_cast<CInPort*>(this));
    }
}

void CPort::dropWire(CPort* other)
{
    if (!other || other->out() == out()) {
        // Drop wasn't on a port? or was on a port of the same type? delete wire.
        if (m_wire) {
            delete m_wire;
        }
    } else {
        if (other->out()) {
            // Otherwise connect the other outport with the wire.
            m_wire->setOutPort(dynamic_cast<COutPort*>(other));
        } else if (!other->out()) {
            // Otherwise connect the other inport with the wire.
            m_wire->setInPort(dynamic_cast<CInPort*>(other));
        }
        other->setWire(m_wire);
        other->connectTo(this);

        m_wire->updatePosition();
    }
}
