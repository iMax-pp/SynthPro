#include "cwire.h"

#include "control/component/cinport.h"
#include "control/component/coutport.h"
#include "control/component/cport.h"
#include "presentation/component/pwire.h"

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

void CWire::updatePosition()
{
    m_presentation->updatePosition();
}

void CWire::midClick()
{
    m_inPort->disconnect();
}
