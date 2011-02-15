#ifndef CVCO_H
#define CVCO_H

#include "abstraction/module/vco.h"
#include "control/cmodule.h"

class CVCO : public VCO, public CModule {
public:
    explicit CVCO(SynthPro*);

    void initialize(SynthProFactory*);
private:
    static QString formatK(qreal);
};

#endif // CVCO_H
