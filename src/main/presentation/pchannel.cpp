#include "pchannel.h"

#include <QPen>

PChannel::PChannel()
    : QGraphicsLineItem(0)
{
    setPen(QPen(Qt::green, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}
