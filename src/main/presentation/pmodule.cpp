#include "pmodule.h"

#include "control/cmodule.h"
#include <QBrush>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QPen>

PModule::PModule(CModule* control)
    : QGraphicsWidget(0)
    , m_control(control)
{
    setFlag(ItemIsMovable);

    // Add a shiny shadow.
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect();
    shadow->setOffset(3);
    shadow->setBlurRadius(9);
    setGraphicsEffect(shadow);
}

void PModule::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setPen(QPen(Qt::darkGreen));
    painter->setBrush(QBrush(Qt::darkCyan));
    painter->drawRect(rect());
}

void PModule::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem::mouseMoveEvent(event);
    m_control->move();
}
