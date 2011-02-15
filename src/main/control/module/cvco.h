#ifndef CVCO_H
#define CVCO_H

#include "abstraction/module/vco.h"
#include "control/cmodule.h"

class CVCO : public VCO, public CModule {
    Q_OBJECT
public:
    explicit CVCO(SynthPro*);

    void initialize(SynthProFactory*);

protected slots:
    void kChanged(qreal);
};

#endif // CVCO_H
