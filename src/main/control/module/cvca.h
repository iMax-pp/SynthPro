#ifndef CVCA_H
#define CVCA_H

#include "abstraction/module/vca.h"
#include "control/cmodule.h"

/**
 * VCA control class (PAC by inheritance).
 */
class CVCA : public VCA, public CModule {
public:
    explicit CVCA(SynthPro*);

    void initialize(SynthProFactory*);

    /// @returns a QString containing the different settings of this Module.
    virtual QString settings() const;

    /// @param settings to set up this Module with.
    virtual void setUpSettings(const QString&);
};

#endif // CVCA_H
