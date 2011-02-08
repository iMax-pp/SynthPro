#include "mockwell.h"

MockWell::MockWell(const QString& msg, QTextStream& s, QObject* parent)
    : MockModule(msg, s, parent)
    , input(this, "input", true) // the input port is replicable
{
    m_inports.append(&input);
}
