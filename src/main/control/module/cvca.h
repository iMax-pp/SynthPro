#ifndef CVCA_H
#define CVCA_H

#include "abstraction/module/vca.h"
#include "control/cmodule.h"

class CVCA : public VCA, public CModule {
public:
    explicit CVCA(SynthPro*);

    void initialize(SynthProFactory*);
private:
    static QString formatGain(qreal);
};

#endif // CVCA_H
