#include "pspeaker.h"

#include "control/module/cspeaker.h"
#include "presentation/component/pvirtualport.h"
#include "presentation/widget/pixmapwidget.h"
#include "presentation/widget/textwidget.h"

#include <QDebug>
#include <QFont>
#include <QGraphicsAnchorLayout>
#include <QIcon>

PSpeaker::PSpeaker(CSpeaker* control)
    : PModule(control)
    , m_clippingLight(0)
    , m_iconClippingLightOn(":/src/resources/images/red-led.png")
    , m_iconClippingLightOff(":/src/resources/images/green-led.png")
{
}

void PSpeaker::initialize(PVirtualPort* in)
{
    TextWidget* title = new TextWidget(tr("Out"), this);
    title->setFont(QFont("Courier", 18, QFont::Bold));

    TextWidget* clipText = new TextWidget(tr("Clip"), this);
    clipText->setFont(QFont("Courier", 8));

    PixmapWidget* speaker = new PixmapWidget(":/src/resources/images/speaker.png", this);

    m_clippingLight = new PixmapWidget(m_iconClippingLightOff, this);

    // Layout
    bottomArea()->addAnchor(clipText, Qt::AnchorRight, m_clippingLight, Qt::AnchorLeft);
    bottomArea()->addAnchor(clipText, Qt::AnchorTop, bottomArea(), Qt::AnchorTop);
    bottomArea()->addCornerAnchors(m_clippingLight, Qt::TopRightCorner, bottomArea(), Qt::TopRightCorner);
    bottomArea()->addCornerAnchors(m_clippingLight, Qt::BottomRightCorner, speaker, Qt::TopRightCorner);
    bottomArea()->addCornerAnchors(speaker, Qt::BottomLeftCorner, bottomArea(), Qt::BottomLeftCorner);
    bottomArea()->addCornerAnchors(speaker, Qt::BottomRightCorner, bottomArea(), Qt::BottomRightCorner);

    leftArea()->addAnchors(in, leftArea());
    centerArea()->addAnchors(title, centerArea());

    bottomArea()->activate();
    layout()->activate();
}

void PSpeaker::clippingStateChanged(bool clippingState)
{
    if (m_clippingLight) {
        m_clippingLight->setPixmap(clippingState ? m_iconClippingLightOn : m_iconClippingLightOff);
    }
}
