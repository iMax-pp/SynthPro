#include "pmodule.h"

#include "control/cmodule.h"
#include <QBrush>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsSceneMouseEvent>
#include <QPen>

PModule::PModule(CModule* control)
    : QGraphicsRectItem(0)
    , m_control(control)
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

void PModule::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem::mouseMoveEvent(event);
    m_control->move();
}
