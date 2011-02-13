#include "mockinoutmodule.h"

#include "factory/synthprofactory.h"

MockInOutModule::MockInOutModule(SynthPro* parent, const QString& msg, QTextStream& s, SynthProFactory* factory)
    : MockModule(parent, msg, s)
    , input(this, "input", factory, true) // The input port is replicable
    , output(this, "output", factory, true) // The output port is replicable
{
    input.initialize();
    output.initialize();
    m_inports.append(&input);
    m_outports.append(&output);
}
