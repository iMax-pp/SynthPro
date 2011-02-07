#ifndef CVCO_H
#define CVCO_H

#include "abstraction/vco.h"
#include "control/cmodule.h"

class CVCO : public VCO, public CModule {
public:
    CVCO(SynthProFactory* factory, QObject* parent = 0);

    void process();
};

#endif // CVCO_H
