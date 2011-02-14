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
}

void PWire::updatePosition(const QPointF& point)
{
    QPointF in = mapFromItem(m_control->inPort()->presentation(),
                             PPort::PORT_SIZE / 2,  PPort::PORT_SIZE / 2);
    QPointF out = point;

    QPainterPath path(in);
    QPointF c1 = QPointF(in.x(), std::max(in.y(), out.y()));
    QPointF c2 = QPointF(out.x(), std::max(in.y(), out.y()));

    // Draw a new path for our wire.
    path.cubicTo(c1, c2, out);
    setPath(path);
}

void PWire::updatePosition()
{
    // Use the outPort as endPoint for updatePosition.
    updatePosition(mapFromItem(m_control->outPort()->presentation(),
                               PPort::PORT_SIZE / 2,  PPort::PORT_SIZE / 2));
}

// TODO really track clicks instead of just press events
void PWire::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::MidButton) {
        event->accept();
        m_control->midClick();
    }
}

void PWire::showMoveFeedback()
{
    QPen p = pen();
    p.setColor(Qt::darkRed);
    setPen(p);
}
