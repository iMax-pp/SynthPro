#ifndef LAYOUTITEM_H
#define LAYOUTITEM_H

#include <QGraphicsItem>

class LayoutItem : public QGraphicsItem {
public:
    LayoutItem(Qt::Orientation, QGraphicsItem*);

    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
    QRectF boundingRect() const;

    // Layout children items according to its orientation
    void doLayout();

protected:
    Qt::Orientation m_orientation;
};

#endif // LAYOUTITEM_H
