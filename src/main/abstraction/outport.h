#ifndef OUT_H
#define OUT_H

#include "port.h"

class OutPort : public Port {
    Q_OBJECT

public:
    OutPort(QObject* parent = 0);

    bool out() const;
};

#endif // OUT_H
