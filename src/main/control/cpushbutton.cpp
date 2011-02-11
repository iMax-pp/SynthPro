#include "cpushbutton.h"

CPushButton::CPushButton(QObject* parent)
    : PushButton(parent)
    , m_presentation(0)
{
}


CPushButton::~CPushButton()
{
    if (m_presentation) {
        delete m_presentation;
    }
}

PPushButton* CPushButton::presentation() const
{
    return m_presentation;
}

void CPushButton::setPresentation(PPushButton* presentation)
{
    m_presentation = presentation;
}
