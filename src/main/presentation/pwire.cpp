#include "pwire.h"

#include "control/cinport.h"
#include "control/coutport.h"
#include "control/cwire.h"
#include "presentation/pport.h"
#include <QApplication>
#include <QDebug>
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

void PWire::updatePosition(QPointF point)
{
    // At least one of the two ports will be defined when creating the wire,
    // so it will always be connected to at least one port.

    QPointF in;
    if (!m_control->inPort()) {
        // Use point if no inPort.
        in = point;
    } else {
        // Use inPort otherwise.
        in = mapFromItem(m_control->inPort()->presentation(), PPort::PORT_SIZE / 2, 0);
    }

    QPointF out;
    if (!m_control->outPort()) {
        // Use point if no outPoint
        out = point;
    } else {
        // Use inPort otherwise.
        out = mapFromItem(m_control->outPort()->presentation(), PPort::PORT_SIZE / 2, 0);
    }

    // Draw a new line for our wire.
    QLineF line(in, out);
    setLine(line);
}
