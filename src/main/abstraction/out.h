#ifndef OUT_H
#define OUT_H

#include "port.h"

class Out : public Port {
    Q_OBJECT

public:
    Out(QObject* parent = 0);
};

#endif // OUT_H
