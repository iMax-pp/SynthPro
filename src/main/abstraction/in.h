#ifndef IN_H
#define IN_H

#include <QObject>
#include "port.h"

class In : public Port
{
public:
    In(QObject* parent=0);
};

#endif // IN_H
