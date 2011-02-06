#include "pport.h"

#include <QBrush>
#include <QPen>

PPort::PPort(QGraphicsItem* parent)
    : QGraphicsEllipseItem(parent)
{
    setRect(0, 0, 8, 8);
    setBrush(QBrush(Qt::darkGreen));
    setPen(QPen(Qt::NoPen));
}
