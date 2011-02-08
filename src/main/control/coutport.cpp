#include "coutport.h"

COutPort::COutPort(CModule* parent, const QString& name, bool replicable, bool gate)
    : Port(parent, name, replicable, gate)
    , OutPort(parent, name, replicable, gate)
    , CPort(parent, name, replicable, gate)
{
}
