#include "pmodule.h"

#include <QBrush>
#include <QPen>

PModule::PModule(QGraphicsItem* parent)
    : QGraphicsRectItem(parent)
{
    setRect(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    setPen(QPen(Qt::darkGreen));
    setBrush(QBrush(Qt::darkCyan));
}
