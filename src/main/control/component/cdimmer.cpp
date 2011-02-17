#include "cdimmer.h"

#include "math.h"

CDimmer::CDimmer(qreal min, qreal max, qreal defaultValue, qreal discretization, QObject* parent)
    : Dimmer(min, max, defaultValue, parent)
    , m_presentation(0)
    , m_discretization(discretization)
    , m_valueFormat(defaultFormat)
{
}

CDimmer::~CDimmer()
{
    if (!m_presentation.isNull()) {
        delete m_presentation;
    }
}

void CDimmer::setPresentation(PDimmer* presentation)
{
    if (!m_presentation.isNull()) {
        delete m_presentation;
    }

    m_presentation = presentation;
    connect(m_presentation, SIGNAL(valueChanged(int)), this, SLOT(valueChanged(int)));
}

void CDimmer::setValueFormat(Format format)
{
    m_valueFormat = format;
    publishValue();
}

void CDimmer::setValue(qreal newValue)
{
    qreal oldValue = value();
    Dimmer::setValue(newValue);
    if (oldValue != value()) {
        publishValue();
    }
}

void CDimmer::publishValue()
{
    if (presentation()) {
        presentation()->updateTitle(m_valueFormat(value()));
    }
}

qreal CDimmer::realValue(qreal value) const
{
    return value * ratio() + offset();
}

void CDimmer::valueChanged(int value)
{
    setValue(value / m_discretization);
}

QString CDimmer::defaultFormat(qreal value)
{
    return QString::number(value, 'g', 4);
}

QString CDimmer::percentageFormat(qreal value)
{
    return QString::number((long)(value * 100)) + "%";
}

QString CDimmer::timeFormat(qreal value)
{
    return QString::number(value, 'g', 2) + "s";
}

QString CDimmer::gainFormat(qreal value)
{
    return QString::number((long)(20 * log10(value))) + " dB";
}
