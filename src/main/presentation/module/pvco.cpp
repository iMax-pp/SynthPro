#include "pvco.h"

#include "control/module/cvco.h"
#include "presentation/component/pdimmer.h"
#include "presentation/component/pselector.h"
#include "presentation/component/pvirtualport.h"
#include "presentation/widget/textwidget.h"

#include <QFont>
#include <QGraphicsAnchorLayout>
#include <QGraphicsSimpleTextItem>

PVCO::PVCO(CVCO* control)
    : PModule(control)
{
}

void PVCO::initialize(PVirtualPort* vfm, PVirtualPort* out, PSelector* selector, PDimmer* k)
{
    TextWidget* title = new TextWidget(tr("VCO"), this);
    title->setFont(QFont("Courier", 18, QFont::Bold));

    k->setSize(80, 80);
    selector->setMaximumSize(120, 155);

    // Layout
    bottomArea()->addCornerAnchors(vfm, Qt::BottomLeftCorner, bottomArea(), Qt::BottomLeftCorner);
    bottomArea()->addCornerAnchors(k, Qt::TopLeftCorner, bottomArea(), Qt::TopLeftCorner);
    bottomArea()->addCornerAnchors(k, Qt::BottomLeftCorner, vfm, Qt::TopLeftCorner);
    bottomArea()->addCornerAnchors(k, Qt::TopRightCorner, selector, Qt::TopLeftCorner);

    bottomArea()->addCornerAnchors(selector, Qt::BottomRightCorner, bottomArea(), Qt::BottomRightCorner);
    bottomArea()->addCornerAnchors(selector, Qt::TopRightCorner, bottomArea(), Qt::TopRightCorner);

    rightArea()->addAnchors(out, rightArea());
    centerArea()->addAnchors(title, centerArea());
}
