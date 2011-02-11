#ifndef INPORT_H
#define INPORT_H

#include "abstraction/virtualport.h"

class InPort : public virtual VirtualPort {
public:
    InPort(Module* parent, const QString& name, SynthProFactory*, bool replicable = false, bool gate = false);

    /**
     * Fetch data from the connections.
     * If this port is replicable, it mixes its inputs
     */
    void fetch();

    // Overriden methods of Module
    inline bool out() const { return false; }
};

#endif // INPORT_H
