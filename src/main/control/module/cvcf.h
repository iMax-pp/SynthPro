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

    /// @returns a QString containing the different settings of this Module.
    virtual QString settings() const;

    /// @param settings to set up this Module with.
    virtual void setUpSettings(const QString&);

protected:
    void filterChanged(int selectedValue);

private:
    static QString formatLPCutOff(qreal);
    static QString formatHPCutOff(qreal);
    static QString formatEmpty(qreal);
    static QString formatResonance(qreal);
};

#endif // CVCF_H
