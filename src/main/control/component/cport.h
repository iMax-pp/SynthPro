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

    /// @returns The associated CVirtualPort.
    inline CVirtualPort* vPort() const { return m_vPort; }

    /// @returns The associated PPort presentation.
    inline PPort* presentation() const { return m_presentation; }

    /// @param presentation of type PPort to associate with this CVirtualPort.
    void setPresentation(PPort*);

    /// @returns The associated CWire.
    inline CWire* wire() const { return m_wire; }

    /// @param wire of type CWire to associate with this CVirtualPort.
    void setWire(CWire*);

    /// Create a temporary wire between a CPort and a given QPointF.
    void createTmpWire(CPort* from, const QPointF& to);

    /// Disconnect the connection.
    void disconnect();
    /// Recreate a new connection.
    void reconnect(const QPointF&);

    /// @returns the reconnecting state.
    inline bool reconnecting() const { return m_reconnecting; }

    /// @param reconnecting state of the port.
    inline void setReconnecting(bool r) { m_reconnecting = r; }

    /*
     * The presentation of this CPort should call these operations
     * when the user attempts to drag and drop from a PortWidget.
     * TODO make these functions protected slots
     */

    /// Called when the drag&drop is started.
    void drag(const QPointF&);
    /// Called when the wire is moved.
    void dragMove(const QPointF&);
    /// Called when the wire is dropped.
    void drop(CPort* target);

    /// Called when the mouse enter the port.
    void mouseEnter();
    /// Called when the mouse leave the port.
    void mouseLeave();

    /// Compatibility feedback.
    void showCompatibleFeedback();
    /// Connectability feedback.
    void showConnectableFeedback();
    /// Unconnectable feedback.
    void showUnconnectableFeedback();
    /// Hide feedback.
    void hideFeedback();

    /// Show availability feedback.
    void showAvailableFeedback();
    /// Hide availability feedback.
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
    CPort* m_oldConnection; // The CPort previously connected to this CPort
                            // (used internally to handle reconnections).
};

#endif // CPORT_H
