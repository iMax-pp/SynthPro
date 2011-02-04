#include "module.h"

Module::Module(QObject* parent)
    : QObject(parent)
{
}

QList<OutPort*>::const_iterator Module::outports() const
{
    return m_outports.begin();
}

QList<InPort*>::const_iterator Module::inports() const
{
    return m_inports.begin();
}
