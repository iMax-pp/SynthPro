#include "pushbutton.h"

#include "abstraction/buffer.h"

PushButton::PushButton(QObject* parent)
    : QObject(parent)
    , m_buffer(new Buffer())
{
    m_buffer->clear();
}

PushButton::~PushButton()
{
    delete m_buffer;
}

Buffer* PushButton::buffer() const
{
    return m_buffer;
}

void PushButton::push()
{
    m_buffer->add(1);
    emit buttonPushed();
}

void PushButton::release()
{
    m_buffer->clear();
    emit buttonReleased();
}
