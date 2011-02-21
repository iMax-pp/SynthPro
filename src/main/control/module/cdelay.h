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

    /// @returns a QString containing the different settings of this Module.
    virtual QString settings() const;

    /// @param settings to set up this Module with.
    virtual void setUpSettings(const QString&);
};

#endif // CDELAY_H
