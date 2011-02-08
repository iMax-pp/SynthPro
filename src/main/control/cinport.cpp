#include "cinport.h"

CInPort::CInPort(CModule* parent, SynthProFactory* factory, bool replicable, bool gate)
    : Port(parent, replicable, gate)
    , InPort(parent, replicable, gate)
    , CPort(parent, factory, replicable, gate)
{
}
