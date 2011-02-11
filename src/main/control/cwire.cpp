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
        m_presentation = 0;
    }
}

void CWire::setPresentation(PWire* presentation)
{
    m_presentation = presentation;
}

void CWire::setInPort(CPort* inPort)
{
    m_inPort = inPort;
}

void CWire::setOutPort(CPort* outPort)
{
    m_outPort = outPort;
}

void CWire::updatePosition(const QPointF& point)
{
    m_presentation->updatePosition(point);
}
