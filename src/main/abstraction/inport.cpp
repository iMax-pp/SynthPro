#include "inport.h"

InPort::InPort(Module* parent)
    : Port(parent)
{
}

bool InPort::out() const
{
    return false;
}
