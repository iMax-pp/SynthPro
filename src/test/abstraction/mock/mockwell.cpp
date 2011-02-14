#include "mockwell.h"

MockWell::MockWell(SynthPro* parent, const QString& msg, QTextStream& s, SynthProFactory* factory)
    : MockModule(parent, msg, s)
    , input(this, "input", factory, true) // the input port is replicable
{
    m_inports.append(&input);
}
