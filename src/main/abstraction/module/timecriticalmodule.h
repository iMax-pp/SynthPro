#ifndef TIMECRITICALMODULE_H
#define TIMECRITICALMODULE_H

#include "abstraction/module.h"

class TimeCriticalModule : public virtual Module {
    Q_OBJECT
public:
    TimeCriticalModule(SynthPro*);

public slots:
    virtual void timerExpired() = 0;
};

#endif // TIMECRITICALMODULE_H
