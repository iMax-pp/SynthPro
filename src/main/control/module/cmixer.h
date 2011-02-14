#ifndef CMIXER_H
#define CMIXER_H

#include "abstraction/module/mixer.h"
#include "control/cmodule.h"

class CMixer : public Mixer, public CModule {
public:
    explicit CMixer(SynthPro*);

    void initialize(SynthProFactory*);
};

#endif // CMIXER_H
