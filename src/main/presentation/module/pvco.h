#ifndef PVCO_H
#define PVCO_H

#include "pmodule.h"

class CVCO;
class PDimmer;
class PVirtualPort;
class PSelector;

class PVCO : public PModule {
public:
    PVCO(CVCO*);

    void initialize(PVirtualPort* vfm, PVirtualPort* out, PSelector*, PDimmer*);
};

#endif // PVCO_H
