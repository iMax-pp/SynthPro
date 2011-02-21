#ifndef CSAMPLER_H
#define CSAMPLER_H

#include "abstraction/module/sampler.h"
#include "control/cmodule.h"

/**
 * Sampler control class (PAC by inheritance).
 */
class CSampler : public Sampler, public CModule {
public:
    explicit CSampler(SynthPro*);

    void initialize(SynthProFactory*);

    /// @returns a QString containing the different settings of this Module.
    virtual QString settings() const;

    /// @param settings to set up this Module with.
    virtual void setUpSettings(const QString&);

private:
    static QString formatSpeed(qreal);
};

#endif // CSAMPLER_H
