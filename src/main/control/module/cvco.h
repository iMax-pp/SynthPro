#ifndef CVCO_H
#define CVCO_H

#include "abstraction/module/vco.h"
#include "control/cmodule.h"

/**
 * VCO control class (PAC by inheritance).
 */
class CVCO : public VCO, public CModule {
public:
    explicit CVCO(SynthPro*);

    void initialize(SynthProFactory*);

    /// @returns a QString containing the different settings of this Module.
    virtual QString settings() const;

    /// @param settings to set up this Module with.
    virtual void setUpSettings(const QString&);

private:
    static QString formatK(qreal);
};

#endif // CVCO_H
