#include "cpushbutton.h"

CPushButton::CPushButton(QObject* parent)
    : PushButton(parent)
    , m_presentation(0)
{
}

PPushButton* CPushButton::presentation() const
{
    return m_presentation;
}

void CPushButton::setPresentation(PPushButton* presentation)
{
    m_presentation = presentation;

    connect(m_presentation, SIGNAL(buttonPushed()), this, SLOT(push()));
    connect(m_presentation, SIGNAL(buttonReleased()), this, SLOT(release()));
}
