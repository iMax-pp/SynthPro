#include "mockwell.h"

MockWell::MockWell(const QString& msg, QTextStream& s, QObject* parent)
    : MockModule(msg, s, parent)
    , input(this)
{
    m_inports.append(&input);
}
