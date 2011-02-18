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
};

#endif // CVCA_H
