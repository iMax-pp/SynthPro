#include "dimmer.h"

Dimmer::Dimmer(qreal min, qreal max, qreal defaultValue, QObject* parent)
    : QObject(parent)
    , m_min(min)
    , m_max(max)
    , m_value(defaultValue)
{
}

void Dimmer::setValue(qreal value)
{
    m_value = value;
}
