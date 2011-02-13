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

    cutOffDimmer->setMaximumSize(90, 90);
    resonance->setMaximumSize(90, 90);
    selector->setMaximumSize(120, 175);

    // Layout
    bottomArea()->addCornerAnchors(cutOff, Qt::BottomLeftCorner, bottomArea(), Qt::BottomLeftCorner);
    bottomArea()->addAnchor(cutOff, Qt::AnchorRight, cutOffDimmer, Qt::AnchorLeft);
    bottomArea()->addAnchor(resonance, Qt::AnchorRight, selector, Qt::AnchorLeft);
    bottomArea()->addAnchor(cutOffDimmer, Qt::AnchorRight, selector, Qt::AnchorLeft);
    bottomArea()->addAnchor(selector, Qt::AnchorRight, bottomArea(), Qt::AnchorRight);
    bottomArea()->addAnchors(selector, bottomArea(), Qt::Vertical);
    bottomArea()->addAnchor(resonance, Qt::AnchorTop, bottomArea(), Qt::AnchorTop);
    bottomArea()->addAnchor(resonance, Qt::AnchorBottom, cutOffDimmer, Qt::AnchorTop);
    bottomArea()->addAnchor(cutOffDimmer, Qt::AnchorBottom, bottomArea(), Qt::AnchorBottom);
    leftArea()->addAnchors(in, leftArea());
    rightArea()->addAnchors(out, rightArea());
    centerArea()->addAnchors(title, centerArea());
}
