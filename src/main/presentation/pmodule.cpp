#include "pmodule.h"

#include <QBrush>
#include <QGraphicsDropShadowEffect>
#include <QPen>

PModule::PModule()
    : QGraphicsRectItem(0)
{
    setFlag(ItemIsMovable);

    setRect(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    setPen(QPen(Qt::darkGreen));
    setBrush(QBrush(Qt::darkCyan));

    // Add a shiny shadow.
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect();
    shadow->setOffset(3);
    shadow->setBlurRadius(9);
    setGraphicsEffect(shadow);
}
