#include "poscilloscopeview.h"

#include "abstraction/module/vco.h"

#include <QDebug>
#include <QPainter>

POscilloscopeView::POscilloscopeView(QGraphicsItem* parent)
    : QGraphicsWidget(parent)
    , m_ratioY(RATIO_Y_DEFAULT)
    , m_stabilized(true)
{
    setMinimumSize(boundingRect().size());
#if QT_VERSION >= 0x040700
    setAutoFillBackground(false);
#endif
}

void POscilloscopeView::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->fillRect(0, 0, WIDTH, HEIGHT, QBrush(Qt::SolidPattern));
    painter->setPen(QPen(QColor(255, 255, 255)));
    painter->setClipping(true);
    painter->setClipRect(0, 0, WIDTH, HEIGHT, Qt::ReplaceClip);

    int currentRatioY = ((HEIGHT / 2) / VCO::SIGNAL_INTENSITY) * m_ratioY;

    int middleY = HEIGHT / 2;
    int previousY = middleY;
    int usedBufferSize = m_inBuffer->length() - BUFFER_INVISIBLE;

    if (m_inBuffer) {
        qreal* data = m_inBuffer->data();
        qreal step;
        int indexBuffer = 0;

        if (m_stabilized) {
            // Find the first high-shelf in a specified interval.
            bool found = false;
            qreal previousValue = 32000;
            qreal currentValue;
            int size = m_inBuffer->length() / 2; // We only test a part of the buffer.

            while (!found && (indexBuffer < size)) {
                currentValue = data[indexBuffer];
                if (previousValue < currentValue) {
                    found = true;
                    // qDebug() << "FOUND !" << indexBuffer << "  Pre = " << previousValue << "  Current = " << currentValue;
                } else {
                    indexBuffer++;
                }
                previousValue = currentValue;
                indexBuffer++;

            }
            if (!found) {
                indexBuffer = 0;
            }
        }

        step = ((usedBufferSize - indexBuffer) / WIDTH);

        for (int i = 0; i < WIDTH ; i++) {
            int y = (int)(middleY - data[(int)indexBuffer] * currentRatioY);
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
