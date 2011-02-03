#include "module.h"

Module::Module(QObject* parent)
    : QObject(parent)
{
}

QList<Out*>::const_iterator Module::outports() const
{
    return m_outports.begin();
}

QList<In*>::const_iterator Module::inports() const
{
    return m_inports.begin();
}
