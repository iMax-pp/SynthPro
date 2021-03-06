#include "pkeyboardkey.h"

#include <QPainter>

PKeyboardKey::PKeyboardKey(QGraphicsItem* parent, int keyNumber, bool whiteKey)
    : QGraphicsWidget(parent)
    , m_keyNumber(keyNumber)
    , m_width(0)
    , m_height(0)
    , m_pressed(false)
    , m_fillKeyBrushPressed(new QBrush(Qt::blue))
{
    setMinimumSize(boundingRect().size());

    if (whiteKey) {
        m_width = WHITE_KEY_WIDTH;
        m_height = WHITE_KEY_HEIGHT;
        m_fillKeyBrush = new QBrush(Qt::white);

    } else {
        m_width = BLACK_KEY_WIDTH;
        m_height = BLACK_KEY_HEIGHT;
        m_fillKeyBrush = new QBrush(Qt::lightGray);
    }
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
    PKeyboardKey::keyPressed();
}

void PKeyboardKey::mouseReleaseEvent(QGraphicsSceneMouseEvent*)
{
    PKeyboardKey::keyReleased();
}

void PKeyboardKey::keyPressed()
{
    m_pressed = true;
    update();
    emit keyboardKeyPressed(m_keyNumber);
}

void PKeyboardKey::keyReleased()
{
    m_pressed = false;
    update();
    emit keyboardKeyReleased(m_keyNumber);
}
