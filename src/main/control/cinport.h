#ifndef CINPORT_H
#define CINPORT_H

#include "abstraction/inport.h"
#include "control/cport.h"

class CInPort : public InPort, public CPort {
public:
    CInPort(Module* parent, bool replicable = false, bool gate = false);

};

#endif // CINPORT_H
