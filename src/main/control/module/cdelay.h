#ifndef CDELAY_H
#define CDELAY_H

#include "abstraction/module/delay.h"
#include "control/cmodule.h"

/**
 * Delay control class (PAC by inheritance).
 */
class CDelay : public Delay, public CModule {
public:
    explicit CDelay(SynthPro*);

    void initialize(SynthProFactory*);
};

#endif // CDELAY_H
