#include "textwidget.h"

#include <QGraphicsSimpleTextItem>
#include <QPainter>

TextWidget::TextWidget(const QString& text, QGraphicsItem* parent)
    : QGraphicsWidget(parent)
    , m_textitem(text, this)
{
    setMinimumSize(childrenBoundingRect().size());
}

void TextWidget::setFont(const QFont& font)
{
    QGraphicsWidget::setFont(font);
    m_textitem.setFont(font);
}
