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

/**
 * Wire control class (PAC by inheritance).
 */
class CWire : public QObject {
public:
    CWire();
    virtual ~CWire();

    /// @returns the associated PWire presentation.
    inline PWire* presentation() const { return m_presentation; }

    /// @param presentation of type PWire to associate with this CWire.
    void setPresentation(PWire*);

    /// @returns The target CPort.
    inline CPort* inPort() const { return m_inPort; }

    /// @returns The source CPort.
    inline CPort* outPort() const { return m_outPort; }

    /// @param target of type CPort to associate with this CWire.
    void setInPort(CPort*);

    /// @param source of type CPort to associate with this CWire.
    void setOutPort(CPort*);

    /**
     * Update the position and length of the wire.
     * @param QPointF representing the non-connected tip when DnD for connection.
     */
    void updatePosition(const QPointF&);

    /**
     * Update the position and length of the wire.
     * Use the two ports as both tips.
     */
    void updatePosition();

    /// Disconnect Wire on duble click.
    void doubleClick();

    /// Show visual feedback when drag&dropping the Wire.
    void showMoveFeedback();

private:
    QPointer<PWire> m_presentation;
    CPort* m_inPort;
    CPort* m_outPort;
};

#endif // CWIRE_H
