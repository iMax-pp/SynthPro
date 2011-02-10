#include "cinport.h"

CInPort::CInPort(CModule* parent, QtFactory* factory, const QString& name, bool replicable, bool gate)
    : VirtualPort(parent, name, replicable, gate)
    , InPort(parent, name, replicable, gate)
    , CVirtualPort(parent, factory, name, replicable, gate)
{
}
