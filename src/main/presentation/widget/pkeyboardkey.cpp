#include "pkeyboardkey.h"

#include <QPainter>

PKeyboardKey::PKeyboardKey(QGraphicsItem* parent, int keyNumber, bool whiteKey, bool assignKey)
    : QGraphicsWidget(parent)
    , m_keyNumber(keyNumber)
    , m_width(0)
    , m_height(0)
    , m_pressed(false)
    , m_fillKeyBrushPressed(new QBrush(Qt::blue))
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

    // If AssignKey is true, a key of the keyboard (to type with) is assigned to (this).
    if (assignKey) {

    }

    setMinimumSize(boundingRect().size());
}

PKeyboardKey::~PKeyboardKey()
{
}

void PKeyboardKey::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setPen(QPen(QColor(0, 0, 0)));
    painter->fillRect(0, 0, m_width, m_height, m_pressed ? *m_fillKeyBrushPressed : *m_fillKeyBrush);
    painter->drawRect(0, 0, m_width, m_height);
}

QRectF PKeyboardKey::boundingRect() const
{
    return QRectF(0, 0, m_width, m_height);
}

void PKeyboardKey::mousePressEvent(QGraphicsSceneMouseEvent*)
{
    m_pressed = true;
    update();
    emit keyboardKeyPressed(m_keyNumber);
}

void PKeyboardKey::mouseReleaseEvent(QGraphicsSceneMouseEvent*)
{
    m_pressed = false;
    update();
    emit keyboardKeyReleased(m_keyNumber);
}
