#include "module.h"

Module::Module(QObject* parent)
{
}
QList<Out> Module::outports() const
{
    return outports;
}

QList<In> Module::inports() const
{
    return inports;
}
