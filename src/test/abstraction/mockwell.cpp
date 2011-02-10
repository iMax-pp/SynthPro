#include "mockwell.h"

MockWell::MockWell(SynthPro* parent, const QString& msg, QTextStream& s)
    : MockModule(parent, msg, s)
    , input(this, "input", true) // the input port is replicable
{
    m_inports.append(&input);
}
