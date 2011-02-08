#ifndef CPORT_H
#define CPORT_H

#include "abstraction/port.h"
#include "presentation/pport.h"

class CPort : public virtual Port {
public:
    CPort(Module* parent, const QString& name, bool replicable = false, bool gate = false);
    virtual ~CPort();

    void setPresentation(PPort*);
    PPort* presentation() const;

private:
    PPort* m_presentation;

};

#endif // CPORT_H
