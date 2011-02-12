#ifndef CWIRE_H
#define CWIRE_H

#include "presentation/component/pwire.h"

#include <QObject>

class CPort;

class CWire : public QObject {
public:
    CWire();
    virtual ~CWire();

    void setPresentation(PWire*);
    inline PWire* presentation() const { return m_presentation; }

    inline CPort* inPort() const { return m_inPort; }
    inline CPort* outPort() const { return m_outPort; }

    void setInPort(CPort*);
    void setOutPort(CPort*);

    /*
     * Update the position and length of the wire.
     * @param QPointF representing the non-connected tip when DnD for connection.
     */
    void updatePosition(const QPointF& = QPointF());

private:
    PWire* m_presentation;
    CPort* m_inPort;
    CPort* m_outPort;
};

#endif // CWIRE_H
