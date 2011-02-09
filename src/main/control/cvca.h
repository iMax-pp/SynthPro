#ifndef CVCA_H
#define CVCA_H

#include "abstraction/vca.h"
#include "cmodule.h"

class CVCA : public VCA, public CModule {
public:
    explicit CVCA(QObject* parent = 0);

    void initialize(SynthProFactory*);
};

#endif // CVCA_H
