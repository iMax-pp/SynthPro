#ifndef CVCO_H
#define CVCO_H

#include "abstraction/vco.h"
#include "cmodule.h"

class CVCO : public VCO, public CModule {
public:
    explicit CVCO(QObject* parent = 0);

    void initialize(SynthProFactory*);
};

#endif // CVCO_H
