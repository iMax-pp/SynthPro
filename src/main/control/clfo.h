#ifndef CLFO_H
#define CLFO_H

#include "abstraction/lfo.h"
#include "control/cmodule.h"

class CLFO : public LFO, public CModule {
public:
    explicit CLFO(SynthPro*);

    void initialize(SynthProFactory*);
};

#endif // CLFO_H
