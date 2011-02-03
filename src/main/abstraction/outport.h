#ifndef OUT_H
#define OUT_H

#include "port.h"

class OutPort : public Port {
    Q_OBJECT

public:
    OutPort(QObject* parent = 0);
};

#endif // OUT_H
