#ifndef PWIRE_H
#define PWIRE_H

#include <QGraphicsLineItem>
#include <QObject>

class CWire;

class PWire : public QGraphicsPathItem, public QObject {
public:
    PWire(CWire*, QGraphicsScene*);

    void updatePosition(const QPointF&);
    void updatePosition();

    void mousePressEvent(QGraphicsSceneMouseEvent*);

    void showMoveFeedback();

    QPainterPath shape() const;

private:
    CWire* m_control;
    QPointF m_endPoint;
};

#endif // PWIRE_H
