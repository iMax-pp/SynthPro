#include "pushbutton.h"

PushButton::PushButton(QObject* parent)
    : QObject(parent)
    , m_pushed(false)
    , m_enabled(true)
{
}

void PushButton::push()
{
    m_pushed = true;
    emit buttonPushed();
}

void PushButton::release()
{
    m_pushed = false;
    emit buttonReleased();
}

void PushButton::setEnabled(bool enabled)
{
    if (enabled != m_enabled) {
        m_enabled = enabled;
        emit buttonEnabled(enabled);
    }
}
