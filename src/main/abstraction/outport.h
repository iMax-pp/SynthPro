#ifndef OUTPORT_H
#define OUTPORT_H

#include "abstraction/buffer.h"
#include "port.h"

class OutPort : public virtual Port {
    Q_OBJECT

public:
    OutPort(Module* parent, const QString& name, bool replicable = false, bool gate = false);

    inline bool out() const { return true; }
};

#endif // OUTPORT_H
