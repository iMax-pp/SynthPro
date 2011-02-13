#include "connection.h"

#include "abstraction/component/inport.h"
#include "abstraction/component/outport.h"

Connection::Connection(OutPort* source, InPort* target)
    : m_source(source)
    , m_target(target)
{
    source->addConnection(this);
    target->addConnection(this);
}

Connection::~Connection()
{
    m_source->removeConnection(this);
    m_target->removeConnection(this);
}
