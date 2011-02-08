#ifndef CPORT_H
#define CPORT_H

#include "abstraction/port.h"
#include "presentation/pport.h"

class CChannel;
class SynthProFactory;

class CPort : public virtual Port {
public:
    CPort(Module* parent, SynthProFactory*, bool replicable = false, bool gate = false);
    virtual ~CPort();

    void setPresentation(PPort*);
    PPort* presentation() const;

    CChannel* channel() const;
    void startChannel();
    void dropChannel(QGraphicsItem*);

private:
    PPort* m_presentation;
    CChannel* m_channel;
    SynthProFactory* m_factory;
};

#endif // CPORT_H
