#include "outport.h"

#include <QObject>

OutPort::OutPort(QObject* parent)
    : Port(parent)
{
}

bool OutPort::out() const
{
    return true;
}
