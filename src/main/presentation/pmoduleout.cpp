#include "pmoduleout.h"

#include "control/cmoduleout.h"
#include "presentation/pixmapwidget.h"
#include "presentation/pvirtualport.h"
#include "presentation/textwidget.h"

#include <QFont>
#include <QGraphicsAnchorLayout>

PModuleOut::PModuleOut(CModuleOut* control)
    : PModule(control)
{
}

void PModuleOut::initialize(PVirtualPort* in)
{
    TextWidget* title = new TextWidget("Out", this);
    title->setFont(QFont("Courier", 18, QFont::Bold));

    PixmapWidget* speaker = new PixmapWidget(":/src/resources/images/speaker-icon.png", this);

    // Layout
    leftArea()->addAnchors(in, leftArea());
    centerArea()->addAnchors(title, centerArea());
    bottomArea()->addAnchors(speaker, bottomArea());
}
