#include "pdelay.h"

#include "control/module/cdelay.h"
#include "presentation/pdimmer.h"
#include "presentation/pvirtualport.h"
#include "presentation/textwidget.h"

#include <QFont>
#include <QGraphicsAnchorLayout>

PDelay::PDelay(CDelay* control)
    : PModule(control)
{
}

void PDelay::initialize(PVirtualPort* in, PVirtualPort* out, PDimmer* duration, PDimmer* decay)
{
    TextWidget* title = new TextWidget("Delay", this);
    title->setFont(QFont("Courier", 18, QFont::Bold));

    duration->setMaximumSize(90, 90);
    decay->setMaximumSize(90, 90);

    // Layout
    bottomArea()->addCornerAnchors(duration, Qt::TopLeftCorner, bottomArea(), Qt::TopLeftCorner);
    bottomArea()->addCornerAnchors(decay, Qt::TopRightCorner, bottomArea(), Qt::TopRightCorner);
    bottomArea()->addCornerAnchors(duration, Qt::BottomLeftCorner, bottomArea(), Qt::BottomLeftCorner);
    bottomArea()->addCornerAnchors(decay, Qt::BottomRightCorner, bottomArea(), Qt::BottomRightCorner);
    bottomArea()->addAnchor(duration, Qt::AnchorRight, decay, Qt::AnchorLeft);
    leftArea()->addAnchors(in, leftArea());
    rightArea()->addAnchors(out, rightArea());
    centerArea()->addAnchors(title, centerArea());
}
