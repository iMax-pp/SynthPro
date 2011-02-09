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

void PVCO::initialize(PPort* pVfm, PPort* pOut, PSelector* pSel, PDimmer* pK)
{
    TextWidget* title = new TextWidget("VCO", this);
    title->setFont(QFont("Courier", 18, QFont::Bold));

    pK->setMaximumSize(60, 60);

    pSel->setMaximumSize(120, 175);

    // Layout
    bottomArea()->addCornerAnchors(pVfm, Qt::BottomLeftCorner, bottomArea(), Qt::BottomLeftCorner);
    bottomArea()->addAnchor(pVfm, Qt::AnchorRight, pK, Qt::AnchorLeft);
    bottomArea()->addAnchor(pK, Qt::AnchorRight, pSel, Qt::AnchorLeft);
    bottomArea()->addAnchor(pSel, Qt::AnchorRight, bottomArea(), Qt::AnchorRight);
    bottomArea()->addAnchors(pSel, bottomArea(), Qt::Vertical);
    bottomArea()->addAnchor(pK, Qt::AnchorBottom, bottomArea(), Qt::AnchorBottom);
    rightArea()->addAnchors(pOut, rightArea());
    centerArea()->addAnchors(title, centerArea());
}
