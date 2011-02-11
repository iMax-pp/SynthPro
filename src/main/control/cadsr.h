#ifndef CADSR_H
#define CADSR_H

#include "abstraction/adsr.h"
#include "control/cmodule.h"

class CADSR : public ADSR, public CModule {
public:
    explicit CADSR(SynthPro*);

    void initialize(SynthProFactory*);
};

#endif // CADSR_H
