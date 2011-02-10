#ifndef PVCF_H
#define PVCF_H

#include "pmodule.h"

class CVCF;
class PDimmer;
class PPort;
class PSelector;

class PVCF : public PModule {
public:
    PVCF(CVCF*);

    void initialize(PPort* in, PPort* cutOff, PPort* out, PSelector*,
                    PDimmer* resonance, PDimmer* cutOffDimmer);
};

#endif // PVCF_H
