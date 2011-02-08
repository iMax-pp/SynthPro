#include "cdimmer.h"

CDimmer::CDimmer(qreal min, qreal max, qreal defaultValue, qreal discretization, QObject* parent)
    : Dimmer(min, max, defaultValue, parent)
    , m_presentation(0)
    , m_discretization(discretization)
{
}

PDimmer* CDimmer::presentation() const
{
    return m_presentation;
}

void CDimmer::setPresentation(PDimmer* presentation)
{
    m_presentation = presentation;
    connect(m_presentation, SIGNAL(valueChanged(int)), this, SLOT(valueChanged(int)));
}

void CDimmer::valueChanged(int value)
{
    setValue(value / m_discretization);
}
