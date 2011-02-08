#include "coutport.h"

COutPort::COutPort(CModule* parent, SynthProFactory* factory, bool replicable, bool gate)
    : Port(parent, replicable, gate)
    , OutPort(parent, replicable, gate)
    , CPort(parent, factory, replicable, gate)
{
}
