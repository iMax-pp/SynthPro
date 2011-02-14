#ifndef PWIRE_H
#define PWIRE_H

#include <QGraphicsLineItem>

class CWire;

class PWire : public QGraphicsPathItem {
public:
    PWire(CWire*, QGraphicsScene*);

    void updatePosition(const QPointF&);
    void updatePosition();

    void mousePressEvent(QGraphicsSceneMouseEvent*);

    void showMoveFeedback();

private:
    CWire* m_control;
};

#endif // PWIRE_H
