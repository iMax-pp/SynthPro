#include "dimmer.h"

Dimmer::Dimmer(float min, float max, float defaultValue, QObject *parent)
    : QObject(parent)
    , m_min(min)
    , m_max(max)
    , m_value(defaultValue)

{
}

Dimmer::value()
{
    return m_value;
}

Dimmer::setValue(float value)
{
    m_value = value;
}

