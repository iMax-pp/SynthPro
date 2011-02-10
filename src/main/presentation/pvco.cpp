#include "pvco.h"

#include "control/cvco.h"
#include "presentation/pdimmer.h"
#include "presentation/pport.h"
#include "presentation/pselector.h"
#include "presentation/textwidget.h"

#include <QFont>
#include <QGraphicsAnchorLayout>
#include <QGraphicsSimpleTextItem>

PVCO::PVCO(CVCO* control)
    : PModule(control)
{
}

void PVCO::initialize(PPort* vfm, PPort* out, PSelector* selector, PDimmer* k)
{
    TextWidget* title = new TextWidget("VCO", this);
    title->setFont(QFont("Courier", 18, QFont::Bold));

    k->setMaximumSize(90, 90);
    selector->setMaximumSize(120, 155);

    // Layout
    bottomArea()->addCornerAnchors(vfm, Qt::BottomLeftCorner, bottomArea(), Qt::BottomLeftCorner);
    bottomArea()->addAnchor(vfm, Qt::AnchorRight, k, Qt::AnchorLeft);
    bottomArea()->addAnchor(k, Qt::AnchorRight, selector, Qt::AnchorLeft);
    bottomArea()->addAnchor(selector, Qt::AnchorRight, bottomArea(), Qt::AnchorRight);
    bottomArea()->addAnchors(selector, bottomArea(), Qt::Vertical);
    bottomArea()->addAnchor(k, Qt::AnchorBottom, bottomArea(), Qt::AnchorBottom);
    rightArea()->addAnchors(out, rightArea());
    centerArea()->addAnchors(title, centerArea());
}
