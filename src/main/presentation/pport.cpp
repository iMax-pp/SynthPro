#include "pport.h"

#include "control/cport.h"
#include "presentation/pvirtualport.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyle>

PPort::PPort(CPort* control, QGraphicsItem* parent)
    : QGraphicsWidget(parent)
    , m_control(control)
{
    setMaximumSize(PORT_SIZE, PORT_SIZE);
    setMinimumSize(PORT_SIZE, PORT_SIZE);

    setAcceptHoverEvents(true);

    hideFeedback(); // HACK to init port color.
}

void PPort::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(palette().button());
    painter->drawEllipse(0, 0, PORT_SIZE, PORT_SIZE);
}

void PPort::showFeedback(bool compatible)
{
    QPalette palette(Qt::red);

    if (compatible) {
        palette.setColor(QPalette::Button, Qt::darkGreen);
    }

    setPalette(palette);
    update();
}

void PPort::hideFeedback()
{
    QPalette palette;
    palette.setBrush(QPalette::Button, QApplication::style()->standardPalette().brush(QPalette::Mid));

    setPalette(palette);
    update();
}

void PPort::showClickableFeedback()
{
    QPalette p;
    p.resolve(palette());
    p.setColor(QPalette::Button, Qt::yellow);
    setPalette(p);
}

void PPort::hideClickableFeedback()
{
    hideFeedback();
}

void PPort::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        event->accept();
        control()->drag();
    }
}

void PPort::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    // While the wire isn't connected to another port, update it with the mouse position.
    control()->dragMove(event->scenePos());
    // m_control->wire()->updatePosition(event->scenePos());
}


void PPort::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    // Retrieve a list of the items beneath the mouse.
    QPointF pos = event->scenePos();
    QList<QGraphicsItem*> items = scene()->items(pos);

    // Try to find the port within all the items...
    PPort* target = 0;
    foreach (QGraphicsItem* item, items) {
        // ...by casting it.
        if ((target = dynamic_cast<PPort*>(item))) {
            // If it's the port, then don't go further.
            break;
        }
    }

    // In any case call the control (ie. to connect or delete the associated wire).
    if (target) {
        control()->drop(target->control());
    } else {
        control()->drop(0);
    }
}

void PPort::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    control()->mouseEnter();
    QGraphicsWidget::hoverEnterEvent(event);
}

void PPort::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    control()->mouseLeave();
    QGraphicsWidget::hoverLeaveEvent(event);
}
