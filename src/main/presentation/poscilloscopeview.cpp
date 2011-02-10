#include "poscilloscopeview.h"

#include "abstraction/vco.h"

#include <QPainter>
POscilloscopeView::POscilloscopeView(QGraphicsItem *parent)
    : QGraphicsWidget(parent)
{


    setMinimumSize(boundingRect().size());
 /*
    m_inBuffer = new qreal[BUFFER_SIZE]; // FIXME : Try.
    for (int i = 0; i < BUFFER_SIZE; i++) {
        m_inBuffer[i] = 0;
    }
    */
}

void POscilloscopeView::paint(QPainter* painter, const QStyleOptionGraphicsItem* options, QWidget* widget)
{
    QBrush brush(Qt::SolidPattern); // TODO : create elsewhere.
    painter->fillRect(0, 0, WIDTH, HEIGHT, brush);

    QPen pen(QColor(255, 255, 255)); // TODO : create elsewhere.
    painter->setPen(pen);

    m_ratioY = VCO::SIGNAL_INTENSITY / HEIGHT;

    // FIXME : the more I do, the more it crashes !
/*
    //int indexBuffer = 0;
    int middleY = HEIGHT / 2;
    for (int i = 0; i < WIDTH ; i++) {
        //painter->drawPoint(i, (int)(middleY + m_inBuffer[(int)indexBuffer] * m_ratioY));
        painter->drawPoint(i, middleY);
        //indexBuffer += STEP;
    }
*/
}

QRectF POscilloscopeView::boundingRect() const
{
    return QRectF(0, 0, WIDTH + 10, HEIGHT + 10);
    //return childrenBoundingRect();
}
