#include "portwidget.h"

#include "control/cportwidget.h"
#include "presentation/pport.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyle>

PortWidget::PortWidget(CPortWidget* control, PPort* parent)
    : QGraphicsWidget(parent)
    , m_control(control)
{
    setMaximumSize(PORT_SIZE, PORT_SIZE);
    setMinimumSize(PORT_SIZE, PORT_SIZE);
}

void PortWidget::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(QApplication::style()->standardPalette().brush(QPalette::Mid));
    painter->drawEllipse(0, 0, PORT_SIZE, PORT_SIZE);
}

void PortWidget::showFeedback(bool compatible)
{
    QPalette palette(Qt::red);

    if (compatible) {
        palette.setColor(QPalette::Window, Qt::darkGreen);
    }

    setPalette(palette);
}

void PortWidget::hideFeedback()
{
    QPalette palette;
    palette.setBrush(QPalette::Window, QApplication::style()->standardPalette().brush(QPalette::Mid));

    setPalette(palette);
}

void PortWidget::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        event->accept();
        m_control->drag();
    }
}

void PortWidget::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    // While the wire isn't connected to another port, update it with the mouse position.
    m_control->dragMove(event->scenePos());
    // m_control->wire()->updatePosition(event->scenePos());
}


void PortWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    // Retrieve a list of the items beneath the mouse.
    QPointF pos = event->scenePos();
    QList<QGraphicsItem*> items = scene()->items(pos);

    // Try to find the port within all the items...
    PortWidget* port = 0;
    foreach (QGraphicsItem* item, items) {
        // ...by casting it.
        if ((port = dynamic_cast<PortWidget*>(item))) {
            // If it's the port, then don't go further.
            break;
        }
    }

    // In any case call the control (ie. to connect or delete the associated wire).
    if (port) {
        m_control->drop(port->control());
    } else {
        m_control->drop(0);
    }
}
