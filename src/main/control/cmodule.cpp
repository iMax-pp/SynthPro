#include "cmodule.h"

#include "abstraction/inport.h"
#include "abstraction/outport.h"
#include "cchannel.h"
#include "cport.h"

CModule::CModule(QObject* parent)
    : Module(parent)
    , m_presentation(0)
{
}

CModule::~CModule()
{
    if (m_presentation) {
        delete m_presentation;
    }
}

void CModule::setPresentation(PModule* presentation)
{
    if (m_presentation) {
        delete m_presentation;
    }

    m_presentation = presentation;
}

PModule* CModule::presentation() const
{
    return m_presentation;
}

void CModule::move()
{
    foreach (InPort* port, m_inports) {
        CChannel* channel = dynamic_cast<CPort*>(port)->channel();
        if (channel) {
            channel->updatePosition();
        }
    }

    foreach (OutPort* port, m_outports) {
        CChannel* channel = dynamic_cast<CPort*>(port)->channel();
        if (channel) {
            channel->updatePosition();
        }
    }
}
