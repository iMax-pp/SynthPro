#include "cinport.h"

#include "control/cmodule.h"
#include "factory/qtfactory.h"

CInPort::CInPort(CModule* parent, QtFactory* factory, const QString& name, bool replicable, bool gate)
    : VirtualPort(parent, name, factory, replicable, gate)
    , InPort(parent, name, factory, replicable, gate)
    , CVirtualPort(parent, factory, name, replicable, gate)
{
}
