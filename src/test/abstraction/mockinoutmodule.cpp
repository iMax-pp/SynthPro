#include "mockinoutmodule.h"

MockInOutModule::MockInOutModule(const QString& msg, QTextStream& s, QObject* parent)
    : MockModule(msg, s, parent)
    , input(this, true) // The input port is replicable
    , output(this, true) // The output port is replicable
{
    m_inports.append(&input);
    m_outports.append(&output);
}
