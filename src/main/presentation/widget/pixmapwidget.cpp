#include "pixmapwidget.h"

#include <QGraphicsPixmapItem>

PixmapWidget::PixmapWidget(QString filename, QGraphicsItem* parent)
    : QGraphicsWidget(parent)
    , m_pixmapItem(QPixmap(filename), this)
{
    setMinimumSize(childrenBoundingRect().size());
    setMaximumSize(childrenBoundingRect().size());
}
