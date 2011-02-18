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
};

#endif // CADSR_H
