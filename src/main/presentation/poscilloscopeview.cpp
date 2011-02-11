#include "poscilloscopeview.h"

#include "abstraction/vco.h"
#include <QPainter>

POscilloscopeView::POscilloscopeView(QGraphicsItem* parent)
    : QGraphicsWidget(parent)
{
    setMinimumSize(boundingRect().size());
}

void POscilloscopeView::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->fillRect(0, 0, WIDTH, HEIGHT, QBrush(Qt::SolidPattern));

    painter->setPen(QPen(QColor(255, 255, 255)));

    m_ratioY = ((HEIGHT / 2) / VCO::SIGNAL_INTENSITY) / 2;

    int indexBuffer = 0;
    int middleY = HEIGHT / 2;

    if (m_inBuffer) {
        qreal* data = m_inBuffer->data();
        qreal step = (m_inBuffer->length() / WIDTH);

        for (int i = 0; i < WIDTH ; i++) {
            painter->drawPoint(i, (int)(middleY + data[(int)indexBuffer] * m_ratioY));
            indexBuffer += step;
        }
    }
}

void POscilloscopeView::setVisualizedBuffer(Buffer* buffer)
{
    m_inBuffer = buffer;
}

QRectF POscilloscopeView::boundingRect() const
{
    return QRectF(-5, -5, WIDTH + 10, HEIGHT + 10);
}
