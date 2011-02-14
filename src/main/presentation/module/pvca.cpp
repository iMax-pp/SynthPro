#include "pvca.h"

#include "control/module/cvca.h"
#include "presentation/component/pdimmer.h"
#include "presentation/component/pvirtualport.h"
#include "presentation/widget/textwidget.h"

#include <QFont>
#include <QGraphicsAnchorLayout>

PVCA::PVCA(CVCA* control)
    : PModule(control)
{
}

void PVCA::initialize(PVirtualPort* in, PVirtualPort* out, PVirtualPort* controlInput, PDimmer* gain)
{
    TextWidget* title = new TextWidget("VCA", this);
    title->setFont(QFont("Courier", 18, QFont::Bold));

    gain->setSize(70, 70);

    // Layout
    bottomArea()->addCornerAnchors(controlInput, Qt::BottomLeftCorner, bottomArea(), Qt::BottomLeftCorner);
    bottomArea()->addCornerAnchors(controlInput, Qt::BottomRightCorner, gain, Qt::BottomLeftCorner);
    bottomArea()->addCornerAnchors(gain, Qt::BottomRightCorner, bottomArea(), Qt::BottomRightCorner);
    bottomArea()->addCornerAnchors(gain, Qt::TopRightCorner, bottomArea(), Qt::TopRightCorner);

    leftArea()->addAnchors(in, leftArea());
    rightArea()->addAnchors(out, rightArea());
    centerArea()->addAnchors(title, centerArea());
}
