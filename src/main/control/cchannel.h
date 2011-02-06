#ifndef CCHANNEL_H
#define CCHANNEL_H

#include "presentation/pchannel.h"

class CInPort;
class COutPort;

class CChannel {
public:
    CChannel();

    void setPresentation(PChannel*);
    PChannel* presentation() const;

    void setInPort(CInPort*);
    void setOutPort(COutPort*);

private:
    PChannel* m_presentation;
    CInPort* m_inPort;
    COutPort* m_outPort;
};

#endif // CCHANNEL_H
