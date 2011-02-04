#include "outport.h"

#include <QObject>

OutPort::OutPort(Module* parent)
    : Port(parent)
{
}

bool OutPort::out() const
{
    return true;
}
