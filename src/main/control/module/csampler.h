#ifndef CSAMPLER_H
#define CSAMPLER_H

#include "abstraction/module/sampler.h"
#include "control/cmodule.h"

class CSampler : public Sampler, public CModule {
public:
    explicit CSampler(SynthPro*);

    void initialize(SynthProFactory*);
};

#endif // CSAMPLER_H
