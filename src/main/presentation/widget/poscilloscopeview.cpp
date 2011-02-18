#include "poscilloscopeview.h"

#include "abstraction/module/vco.h"

#include <QDebug>
#include <QPainter>

POscilloscopeView::POscilloscopeView(QGraphicsItem* parent)
    : QGraphicsWidget(parent)
    , m_inBuffer(0)
    , m_ratioY(RATIO_Y_DEFAULT)
    , m_stabilized(false)
{
    setMinimumSize(boundingRect().size());
#if QT_VERSION >= 0x040700
    setAutoFillBackground(false);
#endif
}

POscilloscopeView::~POscilloscopeView()
{
}

void POscilloscopeView::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->fillRect(0, 0, WIDTH, HEIGHT, QBrush(Qt::SolidPattern));
    painter->setPen(QPen(QColor(255, 255, 255)));
    painter->setClipping(true);
    painter->setClipRect(0, 0, WIDTH, HEIGHT, Qt::ReplaceClip);

    if (!m_inBuffer) {
        return;
    }

    int currentRatioY = ((HEIGHT / 2) / VCO::SIGNAL_INTENSITY) * m_ratioY;

    int middleY = HEIGHT / 2;
    int previousY = middleY;
    int usedBufferSize;

    if (m_inBuffer) {
        qreal* data = m_inBuffer->data();
        qreal step;
        int indexBuffer = 1;

        if (m_stabilized) {
            int scannedSize = SCANNED_WIDTH; // We only test a part of the buffer.

            // If a high-shelf is present at the start, no need to test it.
            bool found = false;
            qreal previousValue = data[0];
            qreal currentValue = data[1];
            if (previousValue > currentValue) {
                found = true;
                previousValue = currentValue;
            }

            // First pass, find high-shelf
            while (!found && (indexBuffer < scannedSize)) {
                currentValue = data[indexBuffer];
                if (previousValue < currentValue) {
                    indexBuffer++;
                    previousValue = currentValue;
                } else {
                    found = true;
                }
            }

            // Second pass, find low-shelf.
            found = false;
            while (!found && (indexBuffer < scannedSize)) {
                currentValue = data[indexBuffer];
                if (previousValue >= currentValue) {
                    indexBuffer++;
                    previousValue = currentValue;
                } else {
                    found = true;
                }
            }

            if (!found) {
                indexBuffer = 0;
            }
        }

        if (m_stabilized) {
            // If stabilized, we need to cut a bit of the signal in order to always display
            // the same amount of data.
            usedBufferSize = m_inBuffer->length() - indexBuffer;
            usedBufferSize = usedBufferSize > MAX_BUFFER_USED ? MAX_BUFFER_USED : usedBufferSize;
        } else {
            usedBufferSize = m_inBuffer->length();
        }

        step = (usedBufferSize / WIDTH);
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

void POscilloscopeView::setStabilized(bool stabilized)
{
    m_stabilized = stabilized;
}

QRectF POscilloscopeView::boundingRect() const
{
    return QRectF(-5, -5, WIDTH + 10, HEIGHT + 10);
}
