#include "cinport.h"

CInPort::CInPort(CModule* parent, const QString& name, bool replicable, bool gate)
    : Port(parent, name, replicable, gate)
    , InPort(parent, name, replicable, gate)
    , CPort(parent, name, replicable, gate)
{
}
