#include "mockmodule.h"

MockModule::MockModule(SynthPro* parent, const QString& msg, QTextStream& s)
    : Module(parent)
    , m_msg(msg)
    , m_s(s)
{
}

void MockModule::ownProcess() { m_s << m_msg; }
