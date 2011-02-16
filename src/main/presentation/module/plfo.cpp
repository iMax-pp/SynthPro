#include "plfo.h"

#include "control/module/clfo.h"
#include "presentation/component/pdimmer.h"
#include "presentation/component/pselector.h"
#include "presentation/component/pvirtualport.h"
#include "presentation/widget/textwidget.h"

#include <QFont>
#include <QGraphicsAnchorLayout>

PLFO::PLFO(CLFO* control)
    : PModule(control)
{
}

void PLFO::initialize(PVirtualPort* out, PDimmer* k, PDimmer* range,
                      PDimmer* offset, PSelector* selector)
{
    TextWidget* title = new TextWidget(tr("LFO"), this);
    title->setFont(QFont("Courier", 18, QFont::Bold));

    k->setSize(80, 80);
    range->setSize(80, 80);
    offset->setSize(80, 80);
    selector->setMaximumSize(120, 155);

    // Layout
    bottomArea()->addCornerAnchors(k, Qt::BottomLeftCorner, bottomArea(), Qt::BottomLeftCorner);
    bottomArea()->addCornerAnchors(k, Qt::BottomRightCorner, offset, Qt::BottomLeftCorner);
    bottomArea()->addCornerAnchors(k, Qt::TopRightCorner, range, Qt::BottomLeftCorner);
    bottomArea()->addCornerAnchors(range, Qt::BottomRightCorner, offset, Qt::TopRightCorner);
    bottomArea()->addCornerAnchors(offset, Qt::BottomRightCorner, selector, Qt::BottomLeftCorner);

    bottomArea()->addCornerAnchors(selector, Qt::BottomRightCorner, bottomArea(), Qt::BottomRightCorner);
    bottomArea()->addCornerAnchors(selector, Qt::TopRightCorner, bottomArea(), Qt::TopRightCorner);

    rightArea()->addAnchors(out, rightArea());
    centerArea()->addAnchors(title, centerArea());
}
