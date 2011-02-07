#include "cinport.h"

CInPort::CInPort(Module* parent, bool replicable, bool gate)
    : Port(parent, replicable, gate)
    , InPort(parent, replicable, gate)
    , CPort(parent, replicable, gate)
{
}
