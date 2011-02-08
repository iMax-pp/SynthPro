#include "clock.h"

#include "module.h"
#include <QTimer>

Clock::Clock(QObject *parent) :
    QObject(parent)
{
}

Clock::~Clock()
{
}

Clock& Clock::instance()
{
    static Clock instance;
    return instance;
}

void Clock::registerFastClock(Module* module)
{
    QTimer* timer = new QTimer(this);
    m_fastTimers.insert(module, timer);
    connect(timer, SIGNAL(timeout()), module, SLOT(timerExpired()));
    timer->start(FAST_TIMER_DELAY);
}

void Clock::unregister(Module* module)
{
    if (m_fastTimers.contains(module)) {
        m_fastTimers.value(module)->stop();
        m_fastTimers.remove(module);
    } else if (m_slowTimers.contains(module)) {
        m_slowTimers.value(module)->stop();
        m_slowTimers.remove(module);
    }
}
