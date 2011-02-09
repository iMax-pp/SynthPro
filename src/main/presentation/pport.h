#ifndef PPORT_H
#define PPORT_H

#include <QGraphicsWidget>

class CPort;
class TextWidget;
class PortWidget;
class QGraphicsLinearLayout;

class PPort : public QGraphicsWidget {
public:
    PPort(CPort*, QGraphicsItem* parent);

    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
    QRectF boundingRect() const;

    CPort* control() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

private:
    CPort* m_control;
    TextWidget* m_label;
    PortWidget* m_port;
    QGraphicsLinearLayout* m_portsLayout;
};

#endif // PPORT_H
