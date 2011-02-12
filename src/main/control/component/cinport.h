#ifndef CINPORT_H
#define CINPORT_H

#include "abstraction/component/inport.h"
#include "control/cmodule.h"
#include "control/component/cvirtualport.h"

class CInPort : public InPort, public CVirtualPort {
public:
    CInPort(CModule* parent, QtFactory*, const QString& name, bool replicable = false, bool gate = false);

};

#endif // CINPORT_H
