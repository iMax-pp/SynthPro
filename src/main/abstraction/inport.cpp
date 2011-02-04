#include "inport.h"

InPort::InPort(Module* parent)
    : Port(parent)
{
}

bool InPort::out() const
{
    return false;
}

Buffer* InPort::buffer()
{
    return m_connection ? m_connection->buffer() : 0;
}
