#ifndef CMIXER_H
#define CMIXER_H

#include "abstraction/module/mixer.h"
#include "control/cmodule.h"

/**
 * CMixer control class (PAC by inheritance).
 */
class CMixer : public Mixer, public CModule {
public:
    explicit CMixer(SynthPro*);

    void initialize(SynthProFactory*);

    /// @returns a QString containing the different settings of this Module.
    virtual QString settings() const;

    /// @param settings to set up this Module with.
    virtual void setUpSettings(const QString&);
};

#endif // CMIXER_H
