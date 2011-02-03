#include "module.h"

Module::Module(QObject* parent):QObject(parent)
{
}
QList<Out> Module::outports() const
{
    return m_outports;
}

QList<In> Module::inports() const
{
    return m_inports;
}
