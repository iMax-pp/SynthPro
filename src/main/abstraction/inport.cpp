#include "inport.h"

InPort::InPort(QObject* parent)
    : Port(parent)
{
}

bool InPort::out() const
{
    return false;
}
