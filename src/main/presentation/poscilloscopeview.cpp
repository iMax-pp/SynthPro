#include "poscilloscopeview.h"

#include "abstraction/vco.h"
#include <QPainter>

POscilloscopeView::POscilloscopeView(QGraphicsItem *parent)
    : QGraphicsWidget(parent)
{
    setMinimumSize(boundingRect().size());

    m_inBuffer = new qreal[Buffer::DEFAULT_LENGTH]; // FIXME : Try.
    for (int i = 0; i < Buffer::DEFAULT_LENGTH; i++) {
        m_inBuffer[i] = 0;
    }
}

void POscilloscopeView::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->fillRect(0, 0, WIDTH, HEIGHT, QBrush(Qt::SolidPattern));

    painter->setPen(QPen(QColor(255, 255, 255)));

    m_ratioY = VCO::SIGNAL_INTENSITY / HEIGHT;

    int indexBuffer = 0;
    int middleY = HEIGHT / 2;

    for (int i = 0; i < WIDTH ; i++) {
        painter->drawPoint(i, (int)(middleY + m_inBuffer[(int)indexBuffer] * m_ratioY));
        indexBuffer += STEP;
    }
}

QRectF POscilloscopeView::boundingRect() const
{
    return QRectF(-5, -5, WIDTH + 10, HEIGHT + 10);
}
