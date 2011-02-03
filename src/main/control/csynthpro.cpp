#include "csynthpro.h"

CSynthPro::CSynthPro()
{
    m_presentation = 0;
}

CSynthPro::~CSynthPro()
{
    if (m_presentation != 0)
        delete m_presentation;
}

void CSynthPro::setPresentation(PSynthPro* p)
{
    if (m_presentation != 0)
        delete m_presentation;
    m_presentation = p;
}
