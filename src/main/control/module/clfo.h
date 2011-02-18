#ifndef CLFO_H
#define CLFO_H

#include "abstraction/module/lfo.h"
#include "control/cmodule.h"

/**
 * CLFO control class (PAC by inheritance).
 */
class CLFO : public LFO, public CModule {
public:
    explicit CLFO(SynthPro*);

    void initialize(SynthProFactory*);

private:
    static QString formatK(qreal);
    static QString formatOffset(qreal);
};

#endif // CLFO_H
