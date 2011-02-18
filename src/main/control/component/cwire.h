#ifndef CWIRE_H
#define CWIRE_H

#include "abstraction/component/connection.h"
#include "presentation/component/pwire.h"

#include <QObject>
#include <QPointer>

class CInPort;
class COutPort;
class CPort;
class QPointF;

class CWire : public QObject {
public:
    CWire();
    virtual ~CWire();

    inline PWire* presentation() const { return m_presentation; }
    void setPresentation(PWire*);

    inline CPort* inPort() const { return m_inPort; }
    inline CPort* outPort() const { return m_outPort; }

    void setInPort(CPort*);
    void setOutPort(CPort*);

    /*
     * Update the position and length of the wire.
     * @param QPointF representing the non-connected tip when DnD for connection.
     */
    void updatePosition(const QPointF&);
    void updatePosition();

    void doubleClick();
    void showMoveFeedback();

private:
    QPointer<PWire> m_presentation;
    CPort* m_inPort;
    CPort* m_outPort;
};

#endif // CWIRE_H
