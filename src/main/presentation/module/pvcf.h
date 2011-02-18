#ifndef PVCF_H
#define PVCF_H

#include "presentation/pmodule.h"

class CVCF;
class PDimmer;
class PVirtualPort;
class PSelector;

class PVCF : public PModule {
public:
    explicit PVCF(CVCF*);

    void initialize(PVirtualPort* in, PVirtualPort* cutOff, PVirtualPort* out, PSelector*,
                    PDimmer* resonance, PDimmer* cutOffDimmer);
};

#endif // PVCF_H
