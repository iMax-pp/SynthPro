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

    inline CPort* control() const { return m_control; }

private:
    CPort* m_control;
    TextWidget* m_label;
    QGraphicsLinearLayout* m_portsLayout;
};

#endif // PPORT_H
