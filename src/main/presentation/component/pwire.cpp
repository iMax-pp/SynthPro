#include "pwire.h"

#include "control/component/cport.h"
#include "control/component/cwire.h"
#include "presentation/component/pport.h"
#include "presentation/component/pvirtualport.h"

#include <QApplication>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QStyle>

PWire::PWire(CWire* control, QGraphicsScene* scene)
    : QGraphicsLineItem(0, scene)
    , m_control(control)
{
    QStyle* style = QApplication::style();
    setPen(QPen(style->standardPalette().brush(QPalette::Shadow), 3,
                Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

QRectF PWire::boundingRect() const
{
    // Thanks to http://doc.qt.nokia.com/latest/graphicsview-diagramscene-arrow-cpp.html
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
           .normalized().adjusted(-extra, -extra, extra, extra);
}

void PWire::updatePosition(const QPointF& point)
{
    QPointF in = mapFromItem(m_control->inPort()->presentation(), PPort::PORT_SIZE / 2,  PPort::PORT_SIZE / 2);
    QPointF out = point;

    // Draw a new line for our wire.
    QLineF line(in, out);
    setLine(line);
}

void PWire::updatePosition()
{
    QPointF in = mapFromItem(m_control->inPort()->presentation(), PPort::PORT_SIZE / 2,  PPort::PORT_SIZE / 2);
    QPointF out = mapFromItem(m_control->outPort()->presentation(), PPort::PORT_SIZE / 2,  PPort::PORT_SIZE / 2);

    // Draw a new line for our wire.
    QLineF line(in, out);
    setLine(line);
}

// TODO really track clicks instead of just press events
void PWire::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::MidButton) {
        event->accept();
        m_control->midClick();
    }
}
