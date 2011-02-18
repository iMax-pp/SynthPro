#include "cpushbutton.h"

CPushButton::CPushButton(QObject* parent)
    : PushButton(parent)
    , m_presentation(0)
{
}

CPushButton::~CPushButton()
{
    if (!m_presentation.isNull()) {
        delete m_presentation;
    }
}

void CPushButton::setPresentation(PPushButton* presentation)
{
    if (!m_presentation.isNull()) {
        delete m_presentation;
    }

    m_presentation = presentation;

    connect(m_presentation, SIGNAL(buttonPushed()), this, SLOT(push()));
    connect(m_presentation, SIGNAL(buttonReleased()), this, SLOT(release()));

    connect(this, SIGNAL(buttonEnabled(bool)), m_presentation, SLOT(setEnabled(bool)));
    connect(this, SIGNAL(buttonCheckable(bool)), m_presentation, SLOT(setCheckable(bool)));
    connect(this, SIGNAL(buttonChecked(bool)), m_presentation, SLOT(setChecked(bool)));
}
