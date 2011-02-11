#include "poscilloscopeview.h"

#include "abstraction/module/vco.h"
#include <QPainter>

POscilloscopeView::POscilloscopeView(QGraphicsItem* parent)
    : QGraphicsWidget(parent)
    , m_ratioY(RATIO_Y_DEFAULT)
{
    setMinimumSize(boundingRect().size());
    setAutoFillBackground(false);
}

void POscilloscopeView::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->fillRect(0, 0, WIDTH, HEIGHT, QBrush(Qt::SolidPattern));
    painter->setPen(QPen(QColor(255, 255, 255)));
    painter->setClipping(true);
    painter->setClipRect(0, 0, WIDTH, HEIGHT, Qt::ReplaceClip);

    int currentRatioY = ((HEIGHT / 2) / VCO::SIGNAL_INTENSITY) * m_ratioY;

    int indexBuffer = 0;
    int middleY = HEIGHT / 2;
    int previousY = middleY;

    if (m_inBuffer) {
        qreal* data = m_inBuffer->data();
        qreal step = (m_inBuffer->length() / WIDTH);

        for (int i = 0; i < WIDTH ; i++) {
            int y = (int)(middleY + data[(int)indexBuffer] * currentRatioY);
            painter->drawLine(i - 1, previousY, i, y);
            previousY = y;
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
