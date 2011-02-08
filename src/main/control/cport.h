#ifndef CPORT_H
#define CPORT_H

#include "abstraction/port.h"
#include "presentation/pport.h"

class CWire;
class SynthProFactory;

class CPort : public virtual Port {
public:
    CPort(Module* parent, SynthProFactory*, const QString& name, bool replicable = false, bool gate = false);
    virtual ~CPort();

    void setPresentation(PPort*);
    PPort* presentation() const;

    CWire* wire() const;
    void setWire(CWire*);

    void startWire();
    void dropWire(PPort*);

private:
    PPort* m_presentation;
    CWire* m_wire;
    SynthProFactory* m_factory;
};

#endif // CPORT_H
