#ifndef PDELAY_H
#define PDELAY_H

#include "presentation/pmodule.h"

class CDelay;
class PDimmer;
class PVirtualPort;

/**
 * Presentation of Delay.
 */
class PDelay : public PModule {
public:
    explicit PDelay(CDelay*);

    void initialize(PVirtualPort* in, PVirtualPort* out, PDimmer* duration, PDimmer* decay);

};

#endif // PDELAY_H
