#include "csynthpro.h"

CSynthPro::CSynthPro()
    : SynthPro()
    , m_presentation(0)
{
}

CSynthPro::~CSynthPro()
{
    if (m_presentation) {
        delete m_presentation;
    }
}

void CSynthPro::setPresentation(PSynthPro* presentation)
{
    if (m_presentation) {
        delete m_presentation;
    }

    m_presentation = presentation;
}

PSynthPro* CSynthPro::getPresentation() const
{
    return m_presentation;
}
