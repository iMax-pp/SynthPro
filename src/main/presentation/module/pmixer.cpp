#include "pmixer.h"

#include "control/module/cmixer.h"
#include "presentation/component/pdimmer.h"
#include "presentation/component/pport.h"
#include "presentation/component/pvirtualport.h"
#include "presentation/widget/textwidget.h"

#include <QGraphicsAnchorLayout>

PMixer::PMixer(CMixer* control)
    : PModule(control)
{
}

void PMixer::initialize(QMap<PVirtualPort*, PDimmer*>& inports, PVirtualPort* out)
{
    TextWidget* title = new TextWidget("Mixer", this);
    title->setFont(QFont("Courier", 18, QFont::Bold));

    PVirtualPort* previousIn = 0;
    PDimmer* previousDimmer = 0;

    foreach (PVirtualPort* in, inports.keys()) {
        PDimmer* dimmer = inports[in];
        dimmer->setMaximumSize(90, 90);

        if (!previousIn) {
            bottomArea()->addAnchor(in, Qt::AnchorTop, bottomArea(), Qt::AnchorTop);
            bottomArea()->addAnchor(dimmer, Qt::AnchorTop, bottomArea(), Qt::AnchorTop);
        } else {
            bottomArea()->addAnchor(in, Qt::AnchorTop, previousIn, Qt::AnchorBottom);
            bottomArea()->addAnchor(dimmer, Qt::AnchorTop, previousDimmer, Qt::AnchorBottom);
        }

        bottomArea()->addAnchor(in, Qt::AnchorLeft, bottomArea(), Qt::AnchorLeft);
        bottomArea()->addAnchor(in, Qt::AnchorRight, dimmer, Qt::AnchorLeft);
        bottomArea()->addAnchor(dimmer, Qt::AnchorRight, bottomArea(), Qt::AnchorRight);

        previousIn = in;
        previousDimmer = dimmer;
    }

    bottomArea()->addAnchor(previousIn, Qt::AnchorBottom, bottomArea(), Qt::AnchorBottom);
    bottomArea()->addAnchor(previousDimmer, Qt::AnchorBottom, bottomArea(), Qt::AnchorBottom);

    rightArea()->addAnchors(out, rightArea());
    centerArea()->addAnchors(title, centerArea());
}
