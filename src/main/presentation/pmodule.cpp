#include "pmodule.h"

#include <QBrush>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsLinearLayout>
#include <QPen>

PModule::PModule()
    : QGraphicsRectItem(0)
    , m_in(0)
    , m_name(0)
    , m_out(0)
    , m_settings(0)
    , m_layout(0)
{
    setFlag(ItemIsMovable);

    setRect(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    setPen(QPen(Qt::darkGreen));
    setBrush(QBrush(Qt::darkCyan));

    // Add a shiny shadow.
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect();
    shadow->setOffset(3);
    shadow->setBlurRadius(9);
    setGraphicsEffect(shadow);

    // Setup layout
    m_layout = new LayoutItem(Qt::Vertical, this);
    LayoutItem* hbox = new LayoutItem(Qt::Horizontal, m_layout);
    m_in = new LayoutItem(Qt::Vertical, hbox);
    m_name = new LayoutItem(Qt::Vertical,  hbox);
    m_out = new LayoutItem(Qt::Vertical, hbox);
    m_settings = new LayoutItem(Qt::Horizontal, m_layout);
}

void PModule::doLayout()
{
    m_layout->doLayout();
}
