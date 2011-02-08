#include "cport.h"

#include "cchannel.h"
#include "cinport.h"
#include "coutport.h"
#include "factory/synthprofactory.h"

CPort::CPort(Module* parent, SynthProFactory* factory, const QString& name, bool replicable, bool gate)
    : Port(parent, name, replicable, gate)
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

void CPort::setChannel(CChannel* channel)
{
    if (channel && m_channel) {
        // If we are not trying to unset the channel and if we already have a channel
        // then delete the current channel.
        delete m_channel;
    }

    m_channel = channel;
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

void CPort::dropChannel(PPort* port)
{
    if (!port || port->control()->out() == out()) {
        // Drop wasn't on a port, or was on a port of the same type, delete channel.
        if (m_channel) {
            delete m_channel;
        }
    } else if (port->control()->out()) {
        // Otherwise connect the other outport with the channel.
        m_channel->setOutPort(dynamic_cast<COutPort*>(port->control()));
        port->control()->setChannel(m_channel);
    } else if (!port->control()->out()) {
        // Otherwise connect the other inport with the channel.
        m_channel->setInPort(dynamic_cast<CInPort*>(port->control()));
        port->control()->setChannel(m_channel);
    }
}
