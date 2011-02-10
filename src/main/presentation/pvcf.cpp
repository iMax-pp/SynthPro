#include "pvcf.h"

#include "control/cvcf.h"
#include "presentation/pdimmer.h"
#include "presentation/pport.h"
#include "presentation/pselector.h"
#include "presentation/textwidget.h"

#include <QFont>
#include <QGraphicsAnchorLayout>

PVCF::PVCF(CVCF* control)
    : PModule(control)
{
}

void PVCF::initialize(PPort* in, PPort* cutOff, PPort* out, PSelector* selector,
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
    bottomArea()->addAnchor(cutOffDimmer, Qt::AnchorRight, resonance, Qt::AnchorLeft);
    bottomArea()->addAnchor(resonance, Qt::AnchorRight, selector, Qt::AnchorLeft);
    bottomArea()->addAnchor(selector, Qt::AnchorRight, bottomArea(), Qt::AnchorRight);
    bottomArea()->addAnchors(selector, bottomArea(), Qt::Vertical);
    bottomArea()->addAnchor(cutOffDimmer, Qt::AnchorBottom, bottomArea(), Qt::AnchorBottom);
    bottomArea()->addAnchor(resonance, Qt::AnchorBottom, bottomArea(), Qt::AnchorBottom);
    leftArea()->addAnchors(in, leftArea());
    rightArea()->addAnchors(out, rightArea());
    centerArea()->addAnchors(title, centerArea());
}
