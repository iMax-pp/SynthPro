#include "cport.h"

#include "cchannel.h"
#include "cinport.h"
#include "coutport.h"
#include "factory/synthprofactory.h"

CPort::CPort(Module* parent, SynthProFactory* factory, bool replicable, bool gate)
    : Port(parent, replicable, gate)
    , m_presentation(0)
    , m_channel(0)
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

CChannel* CPort::channel() const
{
    return m_channel;
}

void CPort::startChannel()
{
    if (m_channel) {
        delete m_channel;
    }

    m_channel = m_factory->createChannel(m_presentation->scene());

    if (out()) {
        m_channel->setOutPort(dynamic_cast<COutPort*>(this));
    } else {
        m_channel->setInPort(dynamic_cast<CInPort*>(this));
    }
}

void CPort::dropChannel(QGraphicsItem* item)
{
    PPort* port = dynamic_cast<PPort*>(item);

    if (!port || port->control()->out() == out()) {
        // Drop wasn't on a PPort, or on a port of the same type, delete channel.
        if (m_channel) {
            delete m_channel;
            m_channel = 0;
        }
    }
}
