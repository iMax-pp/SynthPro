#include "pixmapbuttonwidget.h"

PixmapButtonWidget::PixmapButtonWidget(const QString& fileName, QGraphicsItem* parent)
    : PixmapWidget(fileName, parent)
    , m_activated(true)
    , m_originPos(QPointF())
{
}

void PixmapButtonWidget::setActivated(bool activated)
{
    m_activated = activated;
    setOpacity(m_activated ? 1 : 0.5);
}

void PixmapButtonWidget::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    // Save position for the mouse release.
    m_originPos = pos();

    if (m_activated) {
        setScale(0.9);
        setPos(x() + 1, y() + 1);

        // Forward the event (then emit the clicked signal), only if activated.
        PixmapWidget::mousePressEvent(event);
    }
}

void PixmapButtonWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent*)
{
    setScale(1);
    setPos(m_originPos);
}
