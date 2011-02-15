#ifndef CVCF_H
#define CVCF_H

#include "abstraction/module/vcf.h"
#include "control/cmodule.h"

class CVCF : public VCF, public CModule {
public:
    explicit CVCF(SynthPro*);

    void initialize(SynthProFactory*);
private:
    static QString formatCutOff(qreal);
    static QString formatResonance(qreal);
};

#endif // CVCF_H
