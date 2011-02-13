#include "outport.h"

#include <QObject>

OutPort::OutPort(Module* parent, const QString& name, SynthProFactory* factory, bool replicable, bool gate)
    : VirtualPort(parent, name, factory, replicable, gate)
{
}
