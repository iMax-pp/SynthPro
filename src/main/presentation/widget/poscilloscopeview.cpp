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
    int usedBufferSize = m_inBuffer->length();

    if (m_inBuffer) {
        qreal* data = m_inBuffer->data();
        qreal step;
        int indexBuffer = 1;

        if (m_stabilized) {
            int size = m_inBuffer->length() / 2; // We only test a part of the buffer.

            // Find the first high-shelf in a specified interval.
            bool found = false;
            qreal previousValue = data[0];
            qreal currentValue = data[indexBuffer];
            if (previousValue > currentValue) {
                found = true;
                previousValue = currentValue;
            }

            // First pass, find high-shelf
            while (!found && (indexBuffer < size)) {
                currentValue = data[indexBuffer];
                if (previousValue < currentValue) {
                    indexBuffer++;
                    previousValue = currentValue;
                } else {
                    found = true;
                }
            }

            // Second pass, find low-shelf.
            // if (found) {
                found = false;
                while (!found && (indexBuffer < size)) {
                    currentValue = data[indexBuffer];
                    if (previousValue >= currentValue) {
                        indexBuffer++;
                        previousValue = currentValue;
                    } else {
                        found = true;
                    }
                }
            // }

            /*
                    // Second inner pass.
                    // foundInner = false;
                    innerIndexBuffer = indexBuffer;
                    qreal innerPreviousValue = previousValue;
                    qreal innerCurrentValue;
                    while (!found && (innerIndexBuffer < size)) {
                        innerCurrentValue = data[innerIndexBuffer];
                        if (innerPreviousValue > innerCurrentValue) {
                            found = true;
                        } else {
                            innerIndexBuffer++;
                        }
                        innerPreviousValue = innerCurrentValue;
                    }
                    // found = true;
                    // qDebug() << "FOUND !" << indexBuffer << "  Pre = " << previousValue << "  Current = " << currentValue;
                } else {
                    indexBuffer++;
                }
                previousValue = currentValue;
                indexBuffer++;



            }

            */


            if (!found) {
                indexBuffer = 0;
            } else {
                // indexBuffer = innerIndexBuffer;
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

void POscilloscopeView::setStabilized(bool stabilized)
{
    m_stabilized = stabilized;
}

QRectF POscilloscopeView::boundingRect() const
{
    return QRectF(-5, -5, WIDTH + 10, HEIGHT + 10);
}
