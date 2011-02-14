#include "pvcf.h"

#include "control/module/cvcf.h"
#include "presentation/component/pdimmer.h"
#include "presentation/component/pselector.h"
#include "presentation/component/pvirtualport.h"
#include "presentation/widget/textwidget.h"

#include <QFont>
#include <QGraphicsAnchorLayout>

PVCF::PVCF(CVCF* control)
    : PModule(control)
{
}

void PVCF::initialize(PVirtualPort* in, PVirtualPort* cutOff, PVirtualPort* out, PSelector* selector,
                      PDimmer* resonance, PDimmer* cutOffDimmer)
{
    TextWidget* title = new TextWidget("VCF", this);
    title->setFont(QFont("Courier", 18, QFont::Bold));

    cutOffDimmer->setSize(70, 70);
    resonance->setSize(70, 70);
    selector->setMaximumSize(120, 175);

    // Layout
    bottomArea()->addCornerAnchors(cutOff, Qt::BottomLeftCorner, bottomArea(), Qt::BottomLeftCorner);
    bottomArea()->addCornerAnchors(cutOff, Qt::BottomRightCorner, cutOffDimmer, Qt::BottomLeftCorner);
    bottomArea()->addCornerAnchors(cutOff, Qt::TopRightCorner, resonance, Qt::BottomLeftCorner);
    bottomArea()->addCornerAnchors(resonance, Qt::BottomRightCorner, cutOffDimmer, Qt::TopRightCorner);
    bottomArea()->addCornerAnchors(cutOffDimmer, Qt::BottomRightCorner, selector, Qt::BottomLeftCorner);

    bottomArea()->addCornerAnchors(selector, Qt::BottomRightCorner, bottomArea(), Qt::BottomRightCorner);
    bottomArea()->addCornerAnchors(selector, Qt::TopRightCorner, bottomArea(), Qt::TopRightCorner);

    leftArea()->addAnchors(in, leftArea());
    rightArea()->addAnchors(out, rightArea());
    centerArea()->addAnchors(title, centerArea());
}
