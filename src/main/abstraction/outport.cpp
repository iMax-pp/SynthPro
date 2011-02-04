#include "outport.h"

#include <QObject>

OutPort::OutPort(Module* parent)
    : Port(parent)
    , m_buffer(256) // TODO make the size a parameter of the OutPort constructor
    , m_oldBuffer(256)
{
}

bool OutPort::out() const
{
    return true;
}

Buffer* OutPort::buffer()
{
    return &m_buffer;
}
