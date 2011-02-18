#ifndef OUTPORT_H
#define OUTPORT_H

#include "abstraction/component/virtualport.h"

class OutPort : public virtual VirtualPort {
public:
    OutPort(Module* parent, const QString& name, SynthProFactory*, bool replicable = false, bool gate = false);

    /// Overriden methods of VirtualPort.
    inline bool out() const { return true; }
};

#endif // OUTPORT_H
