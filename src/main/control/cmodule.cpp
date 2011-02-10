#include "cmodule.h"

#include "abstraction/inport.h"
#include "abstraction/outport.h"
#include "control/cport.h"
#include "control/cwire.h"

CModule::CModule(SynthPro* parent)
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
        // Update every inPorts.
        CWire* wire = dynamic_cast<CPort*>(port)->wire();

        if (wire) {
            wire->updatePosition();
        }
    }

    foreach (OutPort* port, m_outports) {
        // Update every outPorts.
        CWire* wire = dynamic_cast<CPort*>(port)->wire();

        if (wire) {
            wire->updatePosition();
        }
    }
}
