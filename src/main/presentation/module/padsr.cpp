#include "padsr.h"

#include "control/module/cadsr.h"
#include "presentation/component/pdimmer.h"
#include "presentation/component/ppushbutton.h"
#include "presentation/component/pvirtualport.h"
#include "presentation/widget/textwidget.h"

#include <QFont>
#include <QGraphicsAnchorLayout>

PADSR::PADSR(CADSR* control)
    : PModule(control)
{
}

void PADSR::initialize(PVirtualPort* gate, PVirtualPort* out, PDimmer* attack, PDimmer* decay,
                       PDimmer* sustain, PDimmer* release, PPushButton* manual)
{
    TextWidget* title = new TextWidget("ADSR", this);
    title->setFont(QFont("Courier", 18, QFont::Bold));

    attack->setSize(70, 70);
    decay->setSize(70, 70);
    sustain->setSize(70, 70);
    release->setSize(70, 70);

    // Layout
    bottomArea()->addCornerAnchors(attack, Qt::TopLeftCorner, bottomArea(), Qt::TopLeftCorner);
    bottomArea()->addCornerAnchors(decay, Qt::TopRightCorner, bottomArea(), Qt::TopRightCorner);
    bottomArea()->addCornerAnchors(sustain, Qt::BottomLeftCorner, bottomArea(), Qt::BottomLeftCorner);
    bottomArea()->addCornerAnchors(release, Qt::BottomRightCorner, bottomArea(), Qt::BottomRightCorner);
    bottomArea()->addCornerAnchors(attack, Qt::BottomRightCorner, release, Qt::TopLeftCorner);
    bottomArea()->addCornerAnchors(sustain, Qt::TopRightCorner, decay, Qt::BottomLeftCorner);

    leftArea()->addCornerAnchors(gate, Qt::TopLeftCorner, leftArea(), Qt::TopLeftCorner);
    leftArea()->addAnchor(manual, Qt::AnchorTop, gate, Qt::AnchorBottom);
    leftArea()->addCornerAnchors(manual, Qt::BottomLeftCorner, leftArea(), Qt::BottomLeftCorner);
    leftArea()->addAnchor(gate, Qt::AnchorRight, leftArea(), Qt::AnchorRight);

    rightArea()->addAnchors(out, rightArea());
    centerArea()->addAnchors(title, centerArea());
}
