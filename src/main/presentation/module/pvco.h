#ifndef PVCO_H
#define PVCO_H

#include "presentation/pmodule.h"

class CVCO;
class PDimmer;
class PVirtualPort;
class PSelector;

/**
 * Presentation of VCO.
 */
class PVCO : public PModule {
public:
    explicit PVCO(CVCO*);

    void initialize(PVirtualPort* vfm, PVirtualPort* out, PSelector*, PDimmer*);
};

#endif // PVCO_H
