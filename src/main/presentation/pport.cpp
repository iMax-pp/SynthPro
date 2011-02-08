#include "pport.h"

#include "control/cchannel.h"
#include "control/cport.h"
#include <QBrush>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPen>

PPort::PPort(CPort* control, QGraphicsItem* parent)
    : QGraphicsEllipseItem(parent)
    , m_control(control)
{
    qDebug(QString("PPort::PPort parent = %1").arg((long)parent).toAscii());
    setRect(0, 0, 10, 10);
    setBrush(QBrush(Qt::darkGreen));
    setPen(QPen(Qt::NoPen));
}

void PPort::mousePressEvent(QGraphicsSceneMouseEvent*)
{
    m_control->startChannel();
}

void PPort::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    m_control->channel()->updatePosition(mapToScene(event->pos()));
}

void PPort::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    m_control->dropChannel(scene()->itemAt(mapToScene(event->pos())));
}

CPort* PPort::control() const
{
    return m_control;
}
