#ifndef PADSR_H
#define PADSR_H

#include "presentation/pmodule.h"

class CADSR;
class PDimmer;
class PVirtualPort;

class PADSR : public PModule {
public:
    PADSR(CADSR*);

    void initialize(PVirtualPort* gate, PVirtualPort* out, PDimmer* attack, PDimmer* decay,
                    PDimmer* sustain, PDimmer* release);

};

#endif // PADSR_H
