#include "outport.h"

#include <QObject>

OutPort::OutPort(Module* parent, bool replicable, bool gate)
    : Port(parent, replicable, gate)
{
    m_buffer = new Buffer();
    m_oldBuffer = new Buffer();
}

OutPort::~OutPort()
{
    delete m_buffer;
    delete m_oldBuffer;
}

bool OutPort::out() const
{
    return true;
}

Buffer* OutPort::buffer()
{
    return m_buffer;
}

void OutPort::swapBuffers()
{
    Buffer* temp = m_buffer;
    m_buffer = m_oldBuffer;
    m_oldBuffer = temp;
}
