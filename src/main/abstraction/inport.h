#ifndef IN_H
#define IN_H

#include "port.h"

class InPort : public Port {
    Q_OBJECT

public:
    InPort(QObject* parent = 0);
};

#endif // IN_H
