#include "selector.h"

Selector::Selector(QList<int> choices, int default_choice, QObject* parent)
    : QObject(parent)
    , m_choices(choices)
    , m_choice(default_choice)
{
}

void Selector::setChoice(int choice)
{
    m_choice = choice;
    emit choiceChanged(m_choice);
}
