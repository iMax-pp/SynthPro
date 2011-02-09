#ifndef PVCO_H
#define PVCO_H

#include "pmodule.h"

class CVCO;
class PDimmer;
class PPort;
class PSelector;

class PVCO : public PModule {
public:
    PVCO(CVCO*);

    void initialize(PPort* vfm, PPort* out, PSelector*, PDimmer*);
};

#endif // PVCO_H
