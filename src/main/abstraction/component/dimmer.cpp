#include "dimmer.h"

Dimmer::Dimmer(qreal min, qreal max, qreal defaultValue, QObject* parent)
    : QObject(parent)
    , m_min(min)
    , m_max(max)
    , m_value(defaultValue)
    , m_offset(0)
    , m_ratio(1)
{
}

void Dimmer::setValue(qreal value)
{
    if (value != m_value) {
        m_value = value;
        emit valueChanged(m_value);
    }
}

void Dimmer::setOffset(qreal offset)
{
    m_offset = offset;
}

void Dimmer::setRatio(qreal ratio)
{
    m_ratio = ratio;
}
