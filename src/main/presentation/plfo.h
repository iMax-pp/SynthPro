#ifndef PLFO_H
#define PLFO_H

#include "presentation/pmodule.h"

class CLFO;
class PDimmer;
class PPort;
class PSelector;

class PLFO : public PModule {
public:
    PLFO(CLFO*);

    void initialize(PPort* out, PDimmer* k, PDimmer* range, PDimmer* offset, PSelector*);

};

#endif // PLFO_H
