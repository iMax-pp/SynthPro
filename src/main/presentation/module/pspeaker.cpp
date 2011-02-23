#include "pspeaker.h"

#include "control/module/cspeaker.h"
#include "presentation/component/ppushbutton.h"
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
    , m_iconClippingLightOn(":/src/resources/images/record-icon.png") // FIXME
    , m_iconClippingLightOff(":/src/resources/images/play-icon.png") // FIXME
{
}

void PSpeaker::initialize(PVirtualPort* in)
{
    TextWidget* title = new TextWidget(tr("Out"), this);
    title->setFont(QFont("Courier", 18, QFont::Bold));

    PixmapWidget* speaker = new PixmapWidget(":/src/resources/images/speaker.png", this);

    m_clippingLight = new PPushButton("Clip", this);
    m_clippingLight->setIcon(m_iconClippingLightOff);
    m_clippingLight->setCheckable(false); // FIXME : doesn't work

    // Layout
    leftArea()->addAnchors(in, leftArea());
    rightArea()->addCornerAnchors(m_clippingLight, Qt::TopLeftCorner, rightArea(), Qt::TopLeftCorner);
    centerArea()->addAnchors(title, centerArea());
    bottomArea()->addAnchors(speaker, bottomArea());

    bottomArea()->activate();
    layout()->activate();
}

void PSpeaker::clippingStateChanged(bool clippingState)
{
    if (m_clippingLight) {
        m_clippingLight->setIcon(clippingState ? m_iconClippingLightOn : m_iconClippingLightOff);
    }
}
