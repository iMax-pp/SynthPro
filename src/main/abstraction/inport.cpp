#include "inport.h"

#include "abstraction/buffer.h"

InPort::InPort(Module* parent, const QString& name, bool replicable, bool gate)
    : Port(parent, name, replicable, gate)
{
    m_buffer = new Buffer();
}

InPort::~InPort()
{
    delete m_buffer;
}

bool InPort::out() const
{
    return false;
}

Buffer* InPort::buffer()
{
    return m_buffer;
}

void InPort::fetch()
{
    m_buffer->clear();

    for (int i = 0; i < m_buffer->length(); i++) {
        foreach (Port* connected, connections()) {
            m_buffer->data()[i] += connected->buffer()->data()[i];
        }
    }
}
