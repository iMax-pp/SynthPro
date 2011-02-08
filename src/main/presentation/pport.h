#ifndef PPORT_H
#define PPORT_H

#include <QGraphicsItem>

class CPort;

class PPort : public QGraphicsItem {
public:
    PPort(CPort* control, QGraphicsItem* parent);

    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
    QRectF boundingRect() const;

private:
    static const int PORT_SIZE = 10;

    QGraphicsSimpleTextItem* m_label;
    QGraphicsEllipseItem* m_port;
};

#endif // PPORT_H
