#ifndef CSAMPLER_H
#define CSAMPLER_H

#include "abstraction/module/sampler.h"
#include "control/cmodule.h"

class CSampler : public Sampler, public CModule {
public:
    explicit CSampler(SynthPro*);

    void initialize(SynthProFactory*);

private:
    static QString formatSpeed(qreal);
};

#endif // CSAMPLER_H
