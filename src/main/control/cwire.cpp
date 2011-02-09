#include "cwire.h"

#include "cinport.h"
#include "coutport.h"

CWire::CWire()
    : QObject(0)
    , m_presentation(0)
    , m_inPort(0)
    , m_outPort(0)
{
}

CWire::~CWire()
{
    if (m_presentation) {
        delete m_presentation;
    }
}

void CWire::setPresentation(PWire* presentation)
{
    m_presentation = presentation;
}

PWire* CWire::presentation() const
{
    return m_presentation;
}

CInPort* CWire::inPort() const
{
    return m_inPort;
}

COutPort* CWire::outPort() const
{
    return m_outPort;
}

void CWire::setInPort(CInPort* inPort)
{
    m_inPort = inPort;
}

void CWire::setOutPort(COutPort* outPort)
{
    m_outPort = outPort;
}

void CWire::updatePosition(QPointF point)
{
    m_presentation->updatePosition(point);
}
