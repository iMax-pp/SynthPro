#include "pkeyboardkey.h"

#include <QPainter>

PKeyboardKey::PKeyboardKey(QGraphicsItem* parent, bool whiteKey)
    : QGraphicsWidget(parent)
    , m_width(0)
    , m_height(0)
{
    if (whiteKey) {
        m_width = WHITE_KEY_WIDTH;
        m_height = WHITE_KEY_HEIGHT;
        m_fillKeyBrush = new QBrush(Qt::white);

    } else {
        m_width = BLACK_KEY_WIDTH;
        m_height = BLACK_KEY_HEIGHT;
        m_fillKeyBrush = new QBrush(Qt::lightGray);
    }

    setMinimumSize(boundingRect().size());
}

void PKeyboardKey::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setPen(QPen(QColor(0, 0, 0)));
    painter->fillRect(0, 0, m_width, m_height, *m_fillKeyBrush);
    painter->drawRect(0, 0, m_width, m_height);
}

QRectF PKeyboardKey::boundingRect() const
{
    return QRectF(0, 0, m_width, m_height);
}
