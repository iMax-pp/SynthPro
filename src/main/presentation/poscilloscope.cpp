#include "poscilloscope.h"

#include "control/coscilloscope.h"
#include "presentation/poscilloscopeview.h"
#include "presentation/pvirtualport.h"
#include "presentation/textwidget.h"

#include <QFont>
#include <QGraphicsAnchorLayout>
#include <QGraphicsSimpleTextItem>

POscilloscope::POscilloscope(COscilloscope* control)
    : PModule(control)
{
    delete m_pOscilloscopeView;
}

void POscilloscope::initialize(PVirtualPort* input)
{
    TextWidget* title = new TextWidget("OSC", this);
    title->setFont(QFont("Courier", 18, QFont::Bold));

    m_pOscilloscopeView = new POscilloscopeView(0);

    //bottomArea()->addCornerAnchors(m_pOscilloscopeView, Qt::BottomLeftCorner, bottomArea(), Qt::BottomLeftCorner);

    // Layout
    // bottomArea()->addCornerAnchors(pVfm, Qt::BottomLeftCorner, bottomArea(), Qt::BottomLeftCorner);
    // bottomArea()->addAnchor(pVfm, Qt::AnchorRight, pK, Qt::AnchorLeft);

    // TODO : Bottom = oscillo. But Crash !!

    leftArea()->addAnchors(input, leftArea());
    rightArea()->addAnchors(m_pOscilloscopeView, rightArea());
    //bottomArea()->addAnchors(m_pOscilloscopeView, bottomArea());
    centerArea()->addAnchors(title, centerArea());
}
