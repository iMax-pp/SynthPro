#ifndef OUTPORT_H
#define OUTPORT_H

#include "abstraction/virtualport.h"

class OutPort : public virtual VirtualPort {
public:
    OutPort(Module* parent, const QString& name, bool replicable = false, bool gate = false);

    inline bool out() const { return true; }
};

#endif // OUTPORT_H
