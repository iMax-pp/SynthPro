#include "pixmapwidget.h"

#include <QGraphicsPixmapItem>

PixmapWidget::PixmapWidget(QString filename, bool showClickable, QGraphicsItem* parent)
    : QGraphicsWidget(parent)
    , m_pixmapItem(QPixmap(filename), this)
    , m_showClickable(showClickable)
{
    setMinimumSize(childrenBoundingRect().size());
    setMaximumSize(childrenBoundingRect().size());
}

void PixmapWidget::mousePressEvent(QGraphicsSceneMouseEvent*)
{
    if (m_showClickable) {
        setScale(0.9);
        setPos(x() + 1, y() + 1);
    }

    emit clicked();
}

void PixmapWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent*)
{
    if (m_showClickable) {
        setScale(1);
        setPos(x() - 1, y() - 1);
    }
}
