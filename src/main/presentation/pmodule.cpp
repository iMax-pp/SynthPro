#include "pmodule.h"

#include <QBrush>
#include <QPen>

PModule::PModule()
    : QGraphicsRectItem(0)
{
    setRect(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    setPen(QPen(Qt::darkGreen));
    setBrush(QBrush(Qt::darkCyan));
}
