#include "coutport.h"

#include "control/cmodule.h"
#include "factory/qtfactory.h"

COutPort::COutPort(CModule* parent, QtFactory* factory, const QString& name, bool replicable, bool gate)
    : VirtualPort(parent, name, factory, replicable, gate)
    , OutPort(parent, name, factory, replicable, gate)
    , CVirtualPort(parent, factory, name, replicable, gate)
{
}
