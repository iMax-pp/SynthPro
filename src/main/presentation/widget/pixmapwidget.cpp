#include "pixmapwidget.h"

#include <QGraphicsPixmapItem>

PixmapWidget::PixmapWidget(const QString& filename, QGraphicsItem* parent)
    : QGraphicsWidget(parent)
    , m_pixmapItem(QPixmap(filename), this)
{
    setMinimumSize(childrenBoundingRect().size());
    setMaximumSize(childrenBoundingRect().size());
}

PixmapWidget::PixmapWidget(const QPixmap& filename, QGraphicsItem* parent)
    : QGraphicsWidget(parent)
    , m_pixmapItem(filename, this)
{
    setMinimumSize(childrenBoundingRect().size());
    setMaximumSize(childrenBoundingRect().size());
}

void PixmapWidget::setPixmap(const QPixmap& filename)
{
    m_pixmapItem.setPixmap(filename);
}

void PixmapWidget::mousePressEvent(QGraphicsSceneMouseEvent*)
{
    emit clicked();
}
