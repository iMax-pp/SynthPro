#include "pport.h"

#include "control/cport.h"
#include "control/cwire.h"
#include <QBrush>
#include <QDebug>
#include <QFont>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPen>

PPort::PPort(CPort* control, QGraphicsItem* parent)
    : QGraphicsItem(parent)
    , m_control(control)
    , m_label(0)
    , m_port(0)
{
    qDebug() << "PPort::PPort parent =" << (long)parent;

    // Create label for port.
    m_label = new QGraphicsSimpleTextItem(this);
    m_label->setText(control->name());
    m_label->setPen(QPen(Qt::black));
    m_label->setFont(QFont("Courier", 10, QFont::Normal));
    m_label->setPos(-m_label->boundingRect().width(),
                    -m_label->boundingRect().height() / 2);

    // Create the port (as an ellipse).
    m_port = new QGraphicsEllipseItem(this);
    m_port->setRect(0, 0, PORT_SIZE, PORT_SIZE);
    m_port->setBrush(QBrush(Qt::darkGreen));
    m_port->setPen(QPen(Qt::NoPen));
    m_port->setPos(0, -m_port->boundingRect().height() / 2);
}

void PPort::paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*)
{
}

QRectF PPort::boundingRect() const
{
    const QRectF& labelBounds = m_label->boundingRect();
    const QRectF& portBounds = m_port->boundingRect();
    return QRectF(-labelBounds.width(), -labelBounds.height() / 2,
                  portBounds.width() + labelBounds.width(),
                  portBounds.height());
}

void PPort::mousePressEvent(QGraphicsSceneMouseEvent*)
{
    // Someone clicked on the port, it's time to start a wire.
    m_control->startWire();
}

void PPort::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    // While the wire isn't connected to another port, update it with the mouse position.
    m_control->wire()->updatePosition(event->scenePos());
}

void PPort::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    // Retrieve a list of the items beneath the mouse.
    QPointF pos = event->scenePos();
    QList<QGraphicsItem*> items = scene()->items(pos);

    // Try to find the port within all the items...
    PPort* port = 0;
    foreach (QGraphicsItem* item, items) {
        // ...by casting it.
        port = dynamic_cast<PPort*>(item);
        if (port) {
            // If it's the port, then don't go further.
            break;
        }
    }

    // In any case call the control (ie. to connect or delete the associated wire).
    if (port) {
        m_control->dropWire(port->control());
    } else {
        m_control->dropWire(0);
    }
}

CPort* PPort::control() const
{
    return m_control;
}
