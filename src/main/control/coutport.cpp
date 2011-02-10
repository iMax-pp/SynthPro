#include "coutport.h"

COutPort::COutPort(CModule* parent, QtFactory* factory, const QString& name, bool replicable, bool gate)
    : Port(parent, name, replicable, gate)
    , OutPort(parent, name, replicable, gate)
    , CPort(parent, factory, name, replicable, gate)
{
}
