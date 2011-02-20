#ifndef PWIRE_H
#define PWIRE_H

#include <QGraphicsLineItem>
#include <QObject>

class CWire;

/**
 * Presentation of a Wire.
 */
class PWire : public QGraphicsPathItem, public QObject {
public:
    PWire(CWire*, QGraphicsScene*);

    /**
     * Visually update the position and length of the wire.
     * @param QPointF representing the non-connected tip when DnD for connection.
     */
    void updatePosition(const QPointF&);

    /**
     * Visually update the position and length of the wire.
     * Use the two ports as both tips.
     */
    void updatePosition();

    /// Intercept double-click event.
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*);

    /// Draw feedback when drag&dropping the wire.
    void showMoveFeedback();

    /// Overriden method to define the exact shape for contains() and update().
    QPainterPath shape() const;

private:
    CWire* m_control;
    QPointF m_endPoint;
};

#endif // PWIRE_H
