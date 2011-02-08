#include "layoutitem.h"

LayoutItem::LayoutItem(Qt::Orientation orientation, QGraphicsItem* parent)
    : QGraphicsItem(parent)
    , m_orientation(orientation)
{
}

void LayoutItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{

}

QRectF LayoutItem::boundingRect() const
{
    return childrenBoundingRect();
}

void LayoutItem::doLayout()
{
    int lengthMax = 0;
    foreach (QGraphicsItem* child, childItems()) {
        // If our children is a layout item, let it lay its item out
        if (LayoutItem* layoutItem = dynamic_cast<LayoutItem*>(child)) {
            layoutItem->doLayout();
        }
        // Find the largest item (in order to center the items)
        if (m_orientation == Qt::Horizontal) {
            int height = child->boundingRect().height();
            if (height > lengthMax) {
                lengthMax = height;
            }
        } else {
            int width = child->boundingRect().width();
            if (width > lengthMax) {
                lengthMax = width;
            }
        }
    }

    int pos = 0;
    foreach (QGraphicsItem* child, childItems()) {
        const QRectF& bounds = child->boundingRect();
        if (m_orientation == Qt::Horizontal) {
            child->setPos(pos, (lengthMax - bounds.height()) / 2);
            pos += bounds.width();
        } else {
            child->setPos(pos, (lengthMax - bounds.width()) / 2);
            pos += bounds.height();
        }
    }
}
