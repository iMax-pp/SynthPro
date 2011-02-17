#include "cselector.h"

CSelector::CSelector(QList<int> choices, int defaultChoice, QObject* parent)
    : Selector(choices, defaultChoice, parent)
    , m_presentation(0)
{
}

CSelector::~CSelector()
{
    if (!m_presentation.isNull()) {
        delete m_presentation;
    }
}

void CSelector::setPresentation(PSelector* presentation)
{
    if (!m_presentation.isNull()) {
        delete m_presentation;
    }

    m_presentation = presentation;

    connect(m_presentation, SIGNAL(choiceChanged(int)), this, SIGNAL(choiceChanged(int)));
    connect(this, SIGNAL(choiceChanged(int)), m_presentation, SLOT(selectButton(int)));
}
