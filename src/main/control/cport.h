#ifndef CPORT_H
#define CPORT_H

#include "abstraction/port.h"
#include "presentation/pport.h"

class CPort /*: virtual public Port*/ {
public:
    // CPort(Module* parent, bool replicable = false, bool gate = false);
    CPort();
    virtual ~CPort();

    void setPresentation(PPort*);
    PPort* presentation() const;

private:
    PPort* m_presentation;

};

#endif // CPORT_H
