#include "mockinoutmodule.h"

MockInOutModule::MockInOutModule(SynthPro* parent, const QString& msg, QTextStream& s)
    : MockModule(parent, msg, s)
    , input(this, "input", true) // The input port is replicable
    , output(this, "output", true) // The output port is replicable
{
    m_inports.append(&input);
    m_outports.append(&output);
}
