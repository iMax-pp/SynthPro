#include "pchannel.h"

#include <QPen>

PChannel::PChannel(QGraphicsItem* parent)
    : QGraphicsLineItem(parent)
{
    setPen(QPen(Qt::green, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}
