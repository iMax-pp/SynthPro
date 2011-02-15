#include "cmodule.h"

#include "abstraction/component/inport.h"
#include "abstraction/component/outport.h"
#include "abstraction/synthpro.h"
#include "control/component/cvirtualport.h"
#include "control/component/cwire.h"
#include <QSignalMapper>

CModule::CModule(SynthPro* parent)
    : Module(parent)
    , m_presentation(0)
{
}

CModule::~CModule()
{
    if (m_presentation) {
        m_presentation->deleteLater();
    }
}

void CModule::setPresentation(PModule* presentation)
{
    if (m_presentation) {
        delete m_presentation;
    }

    m_presentation = presentation;
    QSignalMapper* mapper = new QSignalMapper(this);
    QObject::connect(presentation, SIGNAL(closeBtnClicked()), mapper, SLOT(map()));
    mapper->setMapping(presentation, this);
    QObject::connect(mapper, SIGNAL(mapped(QObject*)), synthPro(), SLOT(remove(QObject*)));
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
