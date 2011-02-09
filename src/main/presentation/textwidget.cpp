#include "textwidget.h"

#include <QPainter>

TextWidget::TextWidget(const QString& text, QGraphicsItem* parent)
    : QGraphicsWidget(parent)
    , m_text(text)
{
}

void TextWidget::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setFont(font());
    painter->drawText(0, 0, m_text);
}
