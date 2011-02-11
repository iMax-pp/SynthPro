#include "pspeaker.h"

#include "control/module/cspeaker.h"
#include "presentation/pixmapwidget.h"
#include "presentation/pvirtualport.h"
#include "presentation/textwidget.h"

#include <QFont>
#include <QGraphicsAnchorLayout>

PSpeaker::PSpeaker(CSpeaker* control)
    : PModule(control)
{
}

void PSpeaker::initialize(PVirtualPort* in)
{
    TextWidget* title = new TextWidget("Out", this);
    title->setFont(QFont("Courier", 18, QFont::Bold));

    PixmapWidget* speaker = new PixmapWidget(":/src/resources/images/speaker-icon.png", this);

    // Layout
    leftArea()->addAnchors(in, leftArea());
    centerArea()->addAnchors(title, centerArea());
    bottomArea()->addAnchors(speaker, bottomArea());
}
