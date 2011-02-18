#ifndef CPORT_H
#define CPORT_H

#include "control/component/cwire.h"
#include "presentation/component/pport.h"
#include <QObject>
#include <QPointer>

class CVirtualPort;
class QPointF;
class QtFactory;

/**
 * Port control class.
 */
class CPort : public QObject {
    Q_OBJECT

public:
    CPort(CVirtualPort* parent, QtFactory*);
    virtual ~CPort();

    inline CVirtualPort* vPort() const { return m_vPort; }

    inline PPort* presentation() const { return m_presentation; }
    void setPresentation(PPort*);

    inline CWire* wire() const { return m_wire; }
    void setWire(CWire*);
    void createTmpWire(CPort* from, const QPointF& to);

    void disconnect();
    void reconnect(const QPointF&);

    inline bool reconnecting() const { return m_reconnecting; }
    inline void setReconnecting(bool r) { m_reconnecting = r; }

    /*
     * The presentation of this CPort should call
     * these operations when the user attempts to drag and
     * drop from a PortWidget
     * TODO make these functions protected slots
     */
    void drag(const QPointF&);
    void dragMove(const QPointF&);
    void drop(CPort* target);

    void mouseEnter();
    void mouseLeave();

    void showFeedback(bool compatible);
    void hideFeedback();

    void showAvailableFeedback();
    void hideAvailableFeedback();

private:
    /// The CVirtualPort owning this CPort
    CVirtualPort* m_vPort;

    QPointer<PPort> m_presentation;

    QtFactory* m_factory;

    /// The wire representing the connection of this CPort
    QPointer<CWire> m_wire;

    /// A temporary wire used during drag
    CWire* m_tmpWire;
    /// A temporary target port used to handle presentation feedback
    PPort* m_dropablePort;

    bool m_reconnecting;
    CPort* m_oldConnection; // The CPort previously connected to this CPort (used internally to handle reconnections)
};

#endif // CPORT_H
