#include "cselector.h"

CSelector::CSelector(QList<int> choices, int defaultChoice, QObject* parent)
    : Selector(choices, defaultChoice, parent)
    , m_presentation(0)
{
}

PSelector* CSelector::presentation() const
{
    return m_presentation;
}

void CSelector::setPresentation(PSelector* presentation)
{
    if (m_presentation) {
        delete m_presentation;
    }

    m_presentation = presentation;

    connect(m_presentation, SIGNAL(choiceChanged(int)), this, SIGNAL(choiceChanged(int)));
}
