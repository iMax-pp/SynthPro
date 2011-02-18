#ifndef COUTPORT_H
#define COUTPORT_H

#include "abstraction/component/outport.h"
#include "control/component/cvirtualport.h"

class CModule;

/**
 * OutPort control class (PAC by inheritance).
 */
class COutPort : public OutPort, public CVirtualPort {
public:
    COutPort(CModule* parent, QtFactory*, const QString& name, bool replicable = false, bool gate = false);
};

#endif // COUTPORT_H
