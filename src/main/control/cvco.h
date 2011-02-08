#ifndef CVCO_H
#define CVCO_H

#include "abstraction/vco.h"
#include "control/cmodule.h"

class CVCO : public VCO, public CModule {
public:
    CVCO(QObject* parent = 0);

    void initialize(SynthProFactory*);
};

#endif // CVCO_H
