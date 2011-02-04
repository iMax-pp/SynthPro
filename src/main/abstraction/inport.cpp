#include "inport.h"

InPort::InPort(Module* parent, bool replicable, bool gate)
    : Port(parent, replicable, gate)
{
}

bool InPort::out() const
{
    return false;
}

Buffer* InPort::buffer()
{
    return 0; // TODO mixer behavior
}
