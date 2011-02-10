#include "inport.h"

#include "abstraction/buffer.h"

InPort::InPort(Module* parent, const QString& name, bool replicable, bool gate)
    : VirtualPort(parent, name, replicable, gate)
{
}

void InPort::fetch()
{
    m_buffer.clear();

    for (int i = 0; i < m_buffer.length(); i++) {
        foreach (VirtualPort* connected, connections()) {
            m_buffer.data()[i] += connected->buffer()->data()[i];
        }
    }
}
