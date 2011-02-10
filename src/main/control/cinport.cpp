#include "cinport.h"

CInPort::CInPort(CModule* parent, QtFactory* factory, const QString& name, bool replicable, bool gate)
    : Port(parent, name, replicable, gate)
    , InPort(parent, name, replicable, gate)
    , CPort(parent, factory, name, replicable, gate)
{
}
