#include "pvco.h"

#include <QFont>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QSlider>

PVCO::PVCO()
{
    // Resize PVCO to integrate the Components nicely.
    setRect(0, 0, 200, 150);

    // Create a Title.
    QGraphicsSimpleTextItem* title = new QGraphicsSimpleTextItem("VCO", this);
    title->setFont(QFont("Courier", 18, QFont::Bold));

    // Create a QSlider.
    QSlider* waveSelector = new QSlider(Qt::Horizontal);
    waveSelector->setTickPosition(QSlider::TicksBelow);
    waveSelector->setRange(0, 3);

    // Add it to the scene using a QGraphicsProxyWidget.
    m_waveSelector = new QGraphicsProxyWidget(this);
    m_waveSelector->setWidget(waveSelector);
    // Static positioning… that ain't nice.
    m_waveSelector->setPos(1, 120);
    m_waveSelector->setMaximumWidth(199);
}
