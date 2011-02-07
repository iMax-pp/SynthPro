#include "cport.h"

CPort::CPort(Module* parent, bool replicable, bool gate)
    : Port(parent, replicable, gate)
    , m_presentation(0)
{
}

CPort::~CPort()
{
    if (m_presentation) {
        delete m_presentation;
    }
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
