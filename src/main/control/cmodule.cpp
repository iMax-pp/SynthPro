#include "cmodule.h"

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
