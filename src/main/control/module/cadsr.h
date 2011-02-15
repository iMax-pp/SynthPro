#ifndef CADSR_H
#define CADSR_H

#include "abstraction/module/adsr.h"
#include "control/cmodule.h"

class CADSR : public ADSR, public CModule {
public:
    explicit CADSR(SynthPro*);

    void initialize(SynthProFactory*);
private:
    static QString formatTime(qreal);
    static QString formatSustain(qreal);
};

#endif // CADSR_H
