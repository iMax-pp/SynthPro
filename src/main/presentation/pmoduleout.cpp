#include "pmoduleout.h"

#include "control/cmoduleout.h"
#include "presentation/pport.h"
#include "presentation/textwidget.h"

#include <QFont>
#include <QGraphicsAnchorLayout>

PModuleOut::PModuleOut(CModuleOut* control)
    : PModule(control)
{
}

void PModuleOut::initialize(PPort* in)
{
    TextWidget* title = new TextWidget("Out", this);
    title->setFont(QFont("Courier", 18, QFont::Bold));

    // Layout
    leftArea()->addAnchors(in, leftArea());
    centerArea()->addAnchors(title, centerArea());
}
