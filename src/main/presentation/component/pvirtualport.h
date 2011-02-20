#ifndef PVIRTUALPORT_H
#define PVIRTUALPORT_H

#include <QGraphicsWidget>

class CVirtualPort;
class TextWidget;
class PPort;
class QGraphicsLinearLayout;

/**
 * Presentation of a VirtualPort.
 * Visually holds the Ports.
 */
class PVirtualPort : public QGraphicsWidget {
public:
    PVirtualPort(CVirtualPort*, QGraphicsItem* parent);

    void initialize(PPort* availablePort);

    /// @returns The associated control of type CVirtualPort.
    inline CVirtualPort* control() const { return m_control; }

    /// Insert a PPort at a given position.
    void insertConnectionPort(int, PPort*);
    /// Remove a given PPort.
    void removeConnectionPort(PPort*);

    /// Self-explanatory method.
    void notifyThatYouCantDropOnARedPort();
    /// Self-explanatory method.
    void notifyThatYouStillCantDropOnARedPort();

private:
    CVirtualPort* m_control;
    TextWidget* m_label;
    QGraphicsLinearLayout* m_connectionsLayout;
};

#endif // PVIRTUALPORT_H
