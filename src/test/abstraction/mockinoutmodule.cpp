#include "mockinoutmodule.h"

MockInOutModule::MockInOutModule(const QString& msg, QTextStream& s, QObject *parent)
    : MockModule(msg, s, parent)
    , input(this)
    , output(this)
{
    m_inports.append(&input);
    m_outports.append(&output);
}
