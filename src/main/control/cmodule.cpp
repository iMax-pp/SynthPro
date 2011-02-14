#include "cmodule.h"

#include "abstraction/component/inport.h"
#include "abstraction/component/outport.h"
#include "control/component/cvirtualport.h"
#include "control/component/cwire.h"

CModule::CModule(SynthPro* parent)
    : Module(parent)
    , m_presentation(0)
{
}

CModule::~CModule()
{
    if (m_presentation) {
        delete m_presentation;
        m_presentation = 0;
    }
}

void CModule::setPresentation(PModule* presentation)
{
    if (m_presentation) {
        delete m_presentation;
        m_presentation = 0;
    }

    m_presentation = presentation;
    connect(presentation, SIGNAL(closeBtnClicked()), new Closer(this), SLOT(onCloseClicked()));
}

PModule* CModule::presentation() const
{
    return m_presentation;
}

void CModule::move()
{
    foreach (InPort* port, m_inports) {
        dynamic_cast<CVirtualPort*>(port)->updateWiresPositions();
    }

    foreach (OutPort* port, m_outports) {
        dynamic_cast<CVirtualPort*>(port)->updateWiresPositions();
    }
}

Closer::Closer(CModule* module)
    : QObject(module)
    , m_module(module)
{

}

void Closer::onCloseClicked()
{
    foreach (InPort* port, m_module->inports()) {
        while (port->connections().size() > 0) {
            port->disconnect(port->connections().first());
        }
    }
    foreach (OutPort* port, m_module->outports()) {
        while (port->connections().size() > 0) {
            port->disconnect(port->connections().first());
        }
    }
    m_module->deleteLater();
}
