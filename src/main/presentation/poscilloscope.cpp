#include "poscilloscope.h"

#include "control/coscilloscope.h"
#include "presentation/pport.h"
#include "presentation/textwidget.h"

#include <QFont>
#include <QGraphicsAnchorLayout>
#include <QGraphicsSimpleTextItem>

POscilloscope::POscilloscope(COscilloscope* control)
    : PModule(control)
{
}

void POscilloscope::initialize(PPort* input)
{
    TextWidget* title = new TextWidget("OSC", this);
    title->setFont(QFont("Courier", 18, QFont::Bold));

    // Layout
    // bottomArea()->addCornerAnchors(pVfm, Qt::BottomLeftCorner, bottomArea(), Qt::BottomLeftCorner);
    // bottomArea()->addAnchor(pVfm, Qt::AnchorRight, pK, Qt::AnchorLeft);
    leftArea()->addAnchors(input, rightArea());
    centerArea()->addAnchors(title, centerArea());

    // TODO : Bottom = oscillo.
}
