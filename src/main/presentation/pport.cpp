#include "pport.h"

#include "control/cport.h"
#include "control/cwire.h"
#include "presentation/portwidget.h"
#include "presentation/textwidget.h"
#include <QDebug>
#include <QFont>
#include <QGraphicsLinearLayout>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

PPort::PPort(CPort* control, QGraphicsItem* parent)
    : QGraphicsWidget(parent)
    , m_control(control)
    , m_label(0)
    , m_port(0)
    , m_portsLayout(0)
{
    // Create label for port.
    m_label = new TextWidget(control->name(), this);
    // m_label->setPen(Qt::NoPen);
    // m_label->setBrush(style->standardPalette().brush(QPalette::ButtonText));
    m_label->setFont(QFont("Courier", 10, QFont::Normal));

    // Create the port (as an ellipse).
    m_port = new PortWidget(this);

    QGraphicsLinearLayout* layout = new QGraphicsLinearLayout(Qt::Horizontal, this);
    m_portsLayout = new QGraphicsLinearLayout(Qt::Vertical, layout);
    if (control->out()) { // Oops some logic in the presentation! I’m so crappy.
        layout->addItem(m_label);
        layout->addItem(m_portsLayout);
    } else {
        layout->addItem(m_portsLayout);
        layout->addItem(m_label);
    }
    m_portsLayout->addItem(m_port);

    setMinimumSize(boundingRect().size());
}

void PPort::paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*)
{
}

QRectF PPort::boundingRect() const
{
    return childrenBoundingRect();
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
        if (PortWidget* portWidget = dynamic_cast<PortWidget*>(item)) {
            port = portWidget->parentPort();
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
