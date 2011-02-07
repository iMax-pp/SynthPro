#include "mockmodule.h"

MockModule::MockModule(const QString& msg, QTextStream& s, QObject* parent)
    : Module(parent)
    , m_msg(msg)
    , m_s(s)
{
}

void MockModule::ownProcess() { m_s << m_msg; }
