#include "coutport.h"

COutPort::COutPort(Module* parent, bool replicable, bool gate)
    : Port(parent, replicable, gate)
    , OutPort(parent, replicable, gate)
    , CPort(parent, replicable, gate)
{
}
