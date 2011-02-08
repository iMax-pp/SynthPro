#include "pvco.h"

#include <QDial>
#include <QFont>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>

PVCO::PVCO()
{
    // TODO move all that code below to the initialize method, using a PDimmer
    // and a PSelector (injected as parameters) instead of QDials.

    // Resize PVCO to integrate the Components nicely.
    setRect(0, 0, 200, 150);

    // Create a Title.
    QGraphicsSimpleTextItem* title = new QGraphicsSimpleTextItem("VCO", this);
    title->setFont(QFont("Courier", 18, QFont::Bold));

    // Create a Wave Selector.
    QDial* waveSelector = new QDial;
    waveSelector->setNotchesVisible(true);
    waveSelector->setRange(0, 4);

    // Add it to the scene using a QGraphicsProxyWidget.
    m_waveSelector = new QGraphicsProxyWidget(this);
    m_waveSelector->setWidget(waveSelector);
    m_waveSelector->setPos(30, 90);
    m_waveSelector->setMaximumSize(50, 50);

    // Create a K Selector.
    QDial* kSelector = new QDial;
    kSelector->setNotchesVisible(true);
    kSelector->setRange(0, 400);

    // Add it to the scene using a QGraphicsProxyWidget.
    m_kSelector = new QGraphicsProxyWidget(this);
    m_kSelector->setWidget(kSelector);
    m_kSelector->setPos(120, 90);
    m_kSelector->setMaximumSize(50, 50);
}

void PVCO::initialize(PPort* vfm, PPort* out)
{
    vfm->setPos(0, 70); // Yes, absolute positioning is bad.
    out->setPos(200, 70);
}
