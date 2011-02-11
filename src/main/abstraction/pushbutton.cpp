#include "pushbutton.h"

PushButton::PushButton(QObject* parent)
    : QObject(parent)
    , m_pushed(false)
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
