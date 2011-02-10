#include "coutport.h"

#include "factory/qtfactory.h"

COutPort::COutPort(CModule* parent, QtFactory* factory, const QString& name, bool replicable, bool gate)
    : VirtualPort(parent, name, replicable, gate)
    , OutPort(parent, name, replicable, gate)
    , CVirtualPort(parent, factory, name, replicable, gate)
{
}
