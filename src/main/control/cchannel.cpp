#include "cchannel.h"

CChannel::CChannel()
    : m_presentation(0)
{
}

void CChannel::setPresentation(PChannel* presentation)
{
    m_presentation = presentation;
}

PChannel* CChannel::presentation() const
{
    return m_presentation;
}

void CChannel::setInPort(CInPort* inPort)
{
    m_inPort = inPort;
}

void CChannel::setOutPort(COutPort* outPort)
{
    m_outPort = outPort;
}
