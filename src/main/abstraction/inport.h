#ifndef IN_H
#define IN_H

#include "port.h"

class InPort : public Port {
    Q_OBJECT

public:
    InPort(Module* parent = 0);

    bool out() const;
    Buffer* buffer();
};

#endif // IN_H
