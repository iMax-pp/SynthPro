#ifndef CADSR_H
#define CADSR_H

#include "abstraction/module/adsr.h"
#include "control/cmodule.h"

/**
 * ADSR control class (PAC by inheritance).
 */
class CADSR : public ADSR, public CModule {
public:
    explicit CADSR(SynthPro*);

    void initialize(SynthProFactory*);

    /// @returns a QString containing the different settings of this Module.
    virtual QString settings() const;

    /// @param settings to set up this Module with.
    virtual void setUpSettings(const QString&);
};

#endif // CADSR_H
