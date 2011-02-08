#ifndef COUTPORT_H
#define COUTPORT_H

#include "abstraction/outport.h"
#include "control/cmodule.h"
#include "control/cport.h"

class COutPort : public OutPort, public CPort {
public:
    COutPort(CModule* parent, SynthProFactory*, bool replicable = false, bool gate = false);
};

#endif // COUTPORT_H
