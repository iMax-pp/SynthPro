#include "port.h"

#include "abstraction/module.h"

Port::Port(Module* parent, bool replicable, bool gate)
    : QObject(parent)
    , m_module(parent)
    , m_replicable(replicable)
    , m_gate(gate)
    , m_connection(0)
{

}

Port::~Port() {}

void Port::connectTo(Port* to)
{
    if (m_connection != to) {
        m_connection = to;
        to->connectTo(this);
        connectedChanged(true); // FIXME This signal will be emitted 2 times, one time for each side of the association
    }
}

bool Port::isConnectable(const Port* to) const
{
    return (!connected() && to->out() != out() && to->gate() == gate());
}
