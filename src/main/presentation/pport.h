#ifndef PPORT_H
#define PPORT_H

#include <QGraphicsItem>

class CPort;

class PPort : public QGraphicsItem {
public:
    PPort(CPort*, QGraphicsItem* parent);

    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
    QRectF boundingRect() const;

    CPort* control() const;

    static const int PORT_SIZE = 15;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

private:
    CPort* m_control;
    QGraphicsSimpleTextItem* m_label;
    QGraphicsEllipseItem* m_port;
};

#endif // PPORT_H
