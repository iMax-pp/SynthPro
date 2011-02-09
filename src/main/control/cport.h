#ifndef CPORT_H
#define CPORT_H

#include "abstraction/port.h"
#include "presentation/pport.h"

class CWire;
class SynthProFactory;

class CPort : public virtual Port {
    Q_OBJECT

public:
    CPort(Module* parent, SynthProFactory*, const QString& name, bool replicable = false, bool gate = false);
    virtual ~CPort();

    void setPresentation(PPort*);
    PPort* presentation() const;

    CWire* wire() const;
    void setWire(CWire*);

    /*
     * Start drawing a wire from this port.
     */
    void startWire();
    /*
     * This method is called when drawing the wire and the mouse dropped it.
     * @param the PPort on which the wire was dropped (may be null).
     */
    void dropWire(CPort*);

protected slots:
    void unsetWire();

private:
    PPort* m_presentation;
    CWire* m_wire;
    SynthProFactory* m_factory;
};

#endif // CPORT_H
