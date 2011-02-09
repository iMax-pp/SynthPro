#include "outport.h"

#include <QObject>

OutPort::OutPort(Module* parent, const QString& name, bool replicable, bool gate)
    : Port(parent, name, replicable, gate)
{
}
