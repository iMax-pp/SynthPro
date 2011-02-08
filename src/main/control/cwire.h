#ifndef CWIRE_H
#define CWIRE_H

#include "presentation/pwire.h"

class CInPort;
class COutPort;

class CWire {
public:
    CWire();
    virtual ~CWire();

    void setPresentation(PWire*);
    PWire* presentation() const;

    CInPort* inPort() const;
    void setInPort(CInPort*);
    COutPort* outPort() const;
    void setOutPort(COutPort*);

    void updatePosition(QPointF = QPointF());

private:
    PWire* m_presentation;
    CInPort* m_inPort;
    COutPort* m_outPort;
};

#endif // CWIRE_H
