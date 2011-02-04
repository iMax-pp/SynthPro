#ifndef CPORT_H
#define CPORT_H

#include "abstraction/port.h"
#include "presentation/pport.h"

class CPort : public Port {
public:
    CPort(Module* parent = 0, bool replicable = false, bool gate = false);
    virtual ~CPort();

    void setPresentation(PPort*);
    PPort* getPresentation() const;

private:
    PPort* m_presentation;

};

#endif // CPORT_H
