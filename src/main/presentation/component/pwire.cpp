#include "pwire.h"

#include "control/component/cport.h"
#include "control/component/cwire.h"
#include "presentation/component/pport.h"
#include "presentation/component/pvirtualport.h"

#include <QApplication>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QStyle>
#include <algorithm>

PWire::PWire(CWire* control, QGraphicsScene* scene)
    : QGraphicsPathItem(0, scene)
    , m_control(control)
{
    QStyle* style = QApplication::style();
    setPen(QPen(style->standardPalette().brush(QPalette::Shadow), 3,
                Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    setZValue(1);
}

void PWire::updatePosition(const QPointF& point)
{
    // Keep the endpoint to calculate the shape() thereafter.
    m_endPoint = point;

    QPointF in = mapFromItem(m_control->inPort()->presentation(),
                             PPort::PORT_SIZE / 2,  PPort::PORT_SIZE / 2);

    QPainterPath path(in);
    QPointF c1 = QPointF(in.x(), std::max(in.y(), m_endPoint.y()) + 20);
    QPointF c2 = QPointF(m_endPoint.x(), std::max(in.y(), m_endPoint.y()) + 20);

    // Draw a new path for our wire.
    path.cubicTo(c1, c2, m_endPoint);
    setPath(path);
}

void PWire::updatePosition()
{
    // Use the outPort as endPoint for updatePosition.
    updatePosition(mapFromItem(m_control->outPort()->presentation(),
                               PPort::PORT_SIZE / 2,  PPort::PORT_SIZE / 2));
}

void PWire::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    event->accept();
    m_control->doubleClick();
}

void PWire::showMoveFeedback()
{
    QPen p = pen();
    p.setColor(Qt::darkRed);
    setPen(p);
}

QPainterPath PWire::shape() const
{
    QPointF in = mapFromItem(m_control->inPort()->presentation(),
                             PPort::PORT_SIZE / 2,  PPort::PORT_SIZE / 2);

    // Calculate an inner path.
    QPainterPath p1(in);
    QPointF c1 = QPointF(in.x(), std::max(in.y(), m_endPoint.y()) + 5);
    QPointF c2 = QPointF(m_endPoint.x(), std::max(in.y(), m_endPoint.y()) + 5);

    p1.cubicTo(c1, c2, m_endPoint);

    // And substract it to the real path.
    QPainterPath p2 = path();
    p2 -= p1;

    // To obtain a path approximately that of the wire.
    return p2;
}
