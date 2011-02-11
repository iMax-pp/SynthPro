#include "plfo.h"

#include "control/module/clfo.h"
#include "presentation/pdimmer.h"
#include "presentation/pselector.h"
#include "presentation/pvirtualport.h"
#include "presentation/textwidget.h"

#include <QFont>
#include <QGraphicsAnchorLayout>

PLFO::PLFO(CLFO* control)
    : PModule(control)
{
}

void PLFO::initialize(PVirtualPort* out, PDimmer* k, PDimmer* range,
                      PDimmer* offset, PSelector* selector)
{
    TextWidget* title = new TextWidget("LFO", this);
    title->setFont(QFont("Courier", 18, QFont::Bold));

    k->setMaximumSize(90, 90);
    range->setMaximumSize(90, 90);
    offset->setMaximumSize(90, 90);
    selector->setMaximumSize(120, 155);

    // Layout
    bottomArea()->addCornerAnchors(k, Qt::BottomLeftCorner, bottomArea(), Qt::BottomLeftCorner);
    bottomArea()->addAnchor(k, Qt::AnchorRight, offset, Qt::AnchorLeft);
    bottomArea()->addAnchor(range, Qt::AnchorRight, selector, Qt::AnchorLeft);
    bottomArea()->addAnchor(offset, Qt::AnchorRight, selector, Qt::AnchorLeft);
    bottomArea()->addAnchor(selector, Qt::AnchorRight, bottomArea(), Qt::AnchorRight);
    bottomArea()->addAnchors(selector, bottomArea(), Qt::Vertical);
    bottomArea()->addAnchor(range, Qt::AnchorTop, bottomArea(), Qt::AnchorTop);
    bottomArea()->addAnchor(range, Qt::AnchorBottom, offset, Qt::AnchorTop);
    bottomArea()->addAnchor(offset, Qt::AnchorBottom, bottomArea(), Qt::AnchorBottom);
    rightArea()->addAnchors(out, rightArea());
    centerArea()->addAnchors(title, centerArea());
}
