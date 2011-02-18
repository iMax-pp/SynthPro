#ifndef CVCF_H
#define CVCF_H

#include "abstraction/module/vcf.h"
#include "control/cmodule.h"

/**
 * VCF control class (PAC by inheritance).
 */
class CVCF : public VCF, public CModule {
public:
    explicit CVCF(SynthPro*);

    void initialize(SynthProFactory*);

protected:
    void filterChanged(int selectedValue);

private:
    static QString formatLPCutOff(qreal);
    static QString formatHPCutOff(qreal);
    static QString formatEmpty(qreal);
    static QString formatResonance(qreal);
};

#endif // CVCF_H
