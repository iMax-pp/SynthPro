#include "cchannel.h"

#include "cinport.h"
#include "coutport.h"

CChannel::CChannel()
    : m_presentation(0)
    , m_inPort(0)
    , m_outPort(0)
{
}

CChannel::~CChannel()
{
    if (m_inPort && m_inPort->channel()) {
        inPort()->setChannel(0);
    }

    if (m_outPort && m_outPort->channel()) {
        outPort()->setChannel(0);
    }

    if (m_presentation) {
        delete m_presentation;
    }
}

void CChannel::setPresentation(PChannel* presentation)
{
    m_presentation = presentation;
}

PChannel* CChannel::presentation() const
{
    return m_presentation;
}

CInPort* CChannel::inPort() const
{
    return m_inPort;
}

void CChannel::setInPort(CInPort* inPort)
{
    m_inPort = inPort;
}

COutPort* CChannel::outPort() const
{
    return m_outPort;
}

void CChannel::setOutPort(COutPort* outPort)
{
    m_outPort = outPort;
}

void CChannel::updatePosition(QPointF point)
{
    m_presentation->updatePosition(point);
}
