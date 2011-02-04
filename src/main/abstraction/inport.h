#ifndef INPORT_H
#define INPORT_H

#include "port.h"

class InPort : public Port {
    Q_OBJECT

public:
    InPort(Module* parent = 0, bool replicable = false, bool gate = false);

    bool out() const;
    Buffer* buffer();
};

#endif // INPORT_H
