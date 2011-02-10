#include "outport.h"

#include <QObject>

OutPort::OutPort(Module* parent, const QString& name, bool replicable, bool gate)
    : VirtualPort(parent, name, replicable, gate)
{
}
