#include "portwidget.h"

#include "presentation/pport.h"
#include <QApplication>
#include <QPainter>
#include <QStyle>

PortWidget::PortWidget(PPort* parent)
    : QGraphicsWidget(parent)
    , m_parent(parent)
{
    setMaximumSize(PORT_SIZE, PORT_SIZE);
    setMinimumSize(PORT_SIZE, PORT_SIZE);
}

void PortWidget::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(QApplication::style()->standardPalette().brush(QPalette::Mid));
    painter->drawEllipse(0, 0, PORT_SIZE, PORT_SIZE);
}
