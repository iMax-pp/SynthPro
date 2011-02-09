#ifndef CVCF_H
#define CVCF_H

#include "abstraction/vcf.h"
#include "cmodule.h"

class CVCF : public VCF, public CModule {
public:
    explicit CVCF(QObject* parent = 0);

    void initialize(SynthProFactory*);
};

#endif // CVCF_H
