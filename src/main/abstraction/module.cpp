#include "module.h"

#include "abstraction/inport.h"
#include "abstraction/outport.h"

Module::Module(QObject* parent)
    : QObject(parent)
{
}

Module::~Module()
{

}

const QList<Module*> Module::getReguirements() const
{
    m_requirements.clear();

    foreach (InPort* port, inports()) {
        if (port->connection())
            m_requirements.append(port->connection()->module());
    }

    return m_requirements;
}
