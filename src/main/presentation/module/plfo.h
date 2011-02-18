#ifndef PLFO_H
#define PLFO_H

#include "presentation/pmodule.h"

class CLFO;
class PDimmer;
class PVirtualPort;
class PSelector;

class PLFO : public PModule {

public:
    explicit PLFO(CLFO*);

    void initialize(PVirtualPort* out, PDimmer* k, PDimmer* range, PDimmer* offset, PSelector*);
};

#endif // PLFO_H
