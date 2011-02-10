#ifndef PADSR_H
#define PADSR_H

#include "presentation/pmodule.h"

class CADSR;
class PDimmer;
class PPort;

class PADSR : public PModule {
public:
    PADSR(CADSR*);

    void initialize(PPort* gate, PPort* out, PDimmer* attack, PDimmer* decay, PDimmer* sustain, PDimmer* release);

};

#endif // PADSR_H
