#ifndef CWIRE_H
#define CWIRE_H

#include "presentation/pwire.h"

#include <QObject>

class CInPort;
class COutPort;

class CWire : public QObject {
public:
    CWire();
    virtual ~CWire();

    void setPresentation(PWire*);
    PWire* presentation() const;

    CInPort* inPort() const;
    COutPort* outPort() const;

    void setInPort(CInPort*);
    void setOutPort(COutPort*);

    /*
     * Update the position and length of the wire.
     * @param QPointF representing the non-connected tip when DnD for connection.
     */
    void updatePosition(QPointF = QPointF());

private:
    PWire* m_presentation;
    CInPort* m_inPort;
    COutPort* m_outPort;
};

#endif // CWIRE_H
