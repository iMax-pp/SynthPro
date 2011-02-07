#include "cport.h"

CPort::CPort(Module* parent, bool replicable, bool gate)
    : Port(parent, replicable, gate)
    , m_presentation(0)
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
