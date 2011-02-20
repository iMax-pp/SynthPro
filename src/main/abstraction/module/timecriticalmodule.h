#ifndef TIMECRITICALMODULE_H
#define TIMECRITICALMODULE_H

#include "abstraction/module.h"

/**
 * Module used when needed time critical accuracy, like the Speaker.
 * Basically, the Clock can register these modules using fast timers,
 * and will call the timerExpired slot when it is expired.
 */
class TimeCriticalModule : public virtual Module {
    Q_OBJECT

public:
    TimeCriticalModule(SynthPro*);

public slots:
    virtual void fastTimerExpired() = 0;
};

#endif // TIMECRITICALMODULE_H
