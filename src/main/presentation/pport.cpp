#include "pport.h"

#include <QBrush>
#include <QPen>

PPort::PPort(QGraphicsItem* parent)
    : QGraphicsEllipseItem(parent)
{
    qDebug(QString("PPort::PPort parent = %1").arg((long)parent).toAscii());
    setRect(0, 0, 10, 10);
    setBrush(QBrush(Qt::darkGreen));
    setPen(QPen(Qt::NoPen));
}
