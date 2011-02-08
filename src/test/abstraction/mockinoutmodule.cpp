#include "mockinoutmodule.h"

MockInOutModule::MockInOutModule(const QString& msg, QTextStream& s, QObject* parent)
    : MockModule(msg, s, parent)
    , input(this, "input", true) // The input port is replicable
    , output(this, "output", true) // The output port is replicable
{
    m_inports.append(&input);
    m_outports.append(&output);
}
