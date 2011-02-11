#include "padsr.h"

#include "control/cadsr.h"
#include "presentation/pdimmer.h"
#include "presentation/ppushbutton.h"
#include "presentation/pselector.h"
#include "presentation/pvirtualport.h"
#include "presentation/textwidget.h"

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

    attack->setMaximumSize(90, 90);
    decay->setMaximumSize(90, 90);
    sustain->setMaximumSize(90, 90);
    release->setMaximumSize(90, 90);

    // Layout
    bottomArea()->addCornerAnchors(attack, Qt::TopLeftCorner, bottomArea(), Qt::TopLeftCorner);
    bottomArea()->addCornerAnchors(decay, Qt::TopRightCorner, bottomArea(), Qt::TopRightCorner);
    bottomArea()->addCornerAnchors(sustain, Qt::BottomLeftCorner, bottomArea(), Qt::BottomLeftCorner);
    bottomArea()->addCornerAnchors(release, Qt::BottomRightCorner, bottomArea(), Qt::BottomRightCorner);
    bottomArea()->addCornerAnchors(attack, Qt::BottomRightCorner, release, Qt::TopLeftCorner);
    bottomArea()->addCornerAnchors(sustain, Qt::TopRightCorner, decay, Qt::BottomLeftCorner);
    leftArea()->addCornerAnchors(gate, Qt::TopLeftCorner, leftArea(), Qt::TopLeftCorner);
    leftArea()->addCornerAnchors(manual, Qt::TopRightCorner, leftArea(), Qt::TopRightCorner);
    leftArea()->addCornerAnchors(gate, Qt::BottomLeftCorner, leftArea(), Qt::BottomLeftCorner);
    leftArea()->addCornerAnchors(manual, Qt::BottomRightCorner, leftArea(), Qt::BottomRightCorner);
    leftArea()->addAnchor(gate, Qt::AnchorRight, manual, Qt::AnchorLeft);
    rightArea()->addAnchors(out, rightArea());
    centerArea()->addAnchors(title, centerArea());
}
