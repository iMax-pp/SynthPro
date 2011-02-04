#ifndef IN_H
#define IN_H

#include "port.h"

class InPort : public Port {
    Q_OBJECT

public:
    InPort(Module* parent = 0);

    bool out() const;
};

#endif // IN_H
