#include "pspeaker.h"

#include "control/module/cspeaker.h"
#include "presentation/component/pvirtualport.h"
#include "presentation/widget/pixmapwidget.h"
#include "presentation/widget/textwidget.h"

#include <QFont>
#include <QGraphicsAnchorLayout>

PSpeaker::PSpeaker(CSpeaker* control)
    : PModule(control)
{
}

void PSpeaker::initialize(PVirtualPort* in)
{
    TextWidget* title = new TextWidget(tr("Out"), this);
    title->setFont(QFont("Courier", 18, QFont::Bold));

    PixmapWidget* speaker = new PixmapWidget(":/src/resources/images/speaker.png", this);

    // Layout
    leftArea()->addAnchors(in, leftArea());
    centerArea()->addAnchors(title, centerArea());
    bottomArea()->addAnchors(speaker, bottomArea());

    bottomArea()->activate();
    layout()->activate();
}
