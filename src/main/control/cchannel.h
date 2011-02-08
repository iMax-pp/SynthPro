#ifndef CCHANNEL_H
#define CCHANNEL_H

#include "presentation/pchannel.h"

class CInPort;
class COutPort;

class CChannel {
public:
    CChannel();
    virtual ~CChannel();

    void setPresentation(PChannel*);
    PChannel* presentation() const;

    CInPort* inPort() const;
    void setInPort(CInPort*);
    COutPort* outPort() const;
    void setOutPort(COutPort*);

    void updatePosition(QPointF = QPointF());

private:
    PChannel* m_presentation;
    CInPort* m_inPort;
    COutPort* m_outPort;
};

#endif // CCHANNEL_H
