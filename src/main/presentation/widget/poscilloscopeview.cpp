#include "poscilloscopeview.h"

#include "abstraction/module/vco.h"

#include <QPainter>

POscilloscopeView::POscilloscopeView(QGraphicsItem* parent)
    : QGraphicsWidget(parent)
    , m_inBuffer(0)
    , m_ratioY(RATIO_Y_DEFAULT)
    , m_stabilized(false)
    , m_penOscillo(QColor(255, 255, 255))
    , m_penOscilloBackground(QColor(0, 255, 0))
    , m_penOscilloHorizontalLimitLine(QColor(255, 0, 0))
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
    // Set up the visualisation box.
    painter->fillRect(0, 0, WIDTH, HEIGHT, QBrush(Qt::SolidPattern));
    painter->setClipping(true);
    painter->setClipRect(0, 0, WIDTH, HEIGHT, Qt::ReplaceClip);

    if (!m_inBuffer) {
        return;
    }

    int currentRatioY = ((HEIGHT / 2) / VCO::SIGNAL_INTENSITY) * m_ratioY;

    int middleY = HEIGHT / 2;
    int previousY = middleY;

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

        int usedBufferSize;

        if (m_stabilized) {
            // If stabilized, we show either the full buffer or the buffer with an offset,
            // depending on which is the shortest.
            usedBufferSize = m_inBuffer->length() - indexBuffer;
            usedBufferSize = usedBufferSize > MAX_BUFFER_USED ? MAX_BUFFER_USED : usedBufferSize;
        } else {
            usedBufferSize = MAX_BUFFER_USED;
        }

        // Display the buffer with the correct radio (both X and Y).
        // Starts with the limit horizontal lines.
        painter->setPen(m_penOscilloHorizontalLimitLine);
        int limitYUp = middleY - VCO::SIGNAL_INTENSITY * currentRatioY;
        int limitYDown = middleY + VCO::SIGNAL_INTENSITY * currentRatioY;
        painter->drawLine(0, limitYUp, WIDTH - 1, limitYUp);
        painter->drawLine(0, limitYDown, WIDTH - 1, limitYDown);

        step = (usedBufferSize / WIDTH); // X ratio.
        for (int i = 0; i < WIDTH ; i++) {
            int y = -(int)(data[(int)indexBuffer] * currentRatioY);
            // Limit test.
            if (y > LIMIT_Y) {
                y = LIMIT_Y;
            } else if (y < -LIMIT_Y) {
                y = -LIMIT_Y;
            }
            y += middleY;

            // Darker vertical line
            painter->setPen(m_penOscilloBackground);
            painter->drawLine(i, y + 1, i, HEIGHT - 1);

            // Lighter line
            painter->setPen(m_penOscillo);
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
