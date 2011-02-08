#include "pport.h"

#include "control/cport.h"
#include <QBrush>
#include <QFont>
#include <QPen>

PPort::PPort(CPort* control, QGraphicsItem* parent)
    : QGraphicsItem(parent)
    , m_label(0)
    , m_port(0)
{
    qDebug(QString("PPort::PPort parent = %1").arg((long)parent).toAscii());

    m_label = new QGraphicsSimpleTextItem(this);
    m_label->setText(control->name());
    m_label->setPen(QPen(Qt::black));
    m_label->setFont(QFont("Courier", 10, QFont::Normal));
    m_label->setPos(-m_label->boundingRect().width(),
                    -m_label->boundingRect().height() / 2);

    m_port = new QGraphicsEllipseItem(this);
    m_port->setRect(0, 0, PORT_SIZE, PORT_SIZE);
    m_port->setBrush(QBrush(Qt::darkGreen));
    m_port->setPen(QPen(Qt::NoPen));
    m_port->setPos(0, -m_port->boundingRect().height() / 2);
}

void PPort::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
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
