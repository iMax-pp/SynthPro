#include "pkeyboard.h"

#include "abstraction/buffer.h"
#include "control/ckeyboard.h"
#include "presentation/pkeyboardview.h"
#include "presentation/pvirtualport.h"
#include "presentation/textwidget.h"

#include <QFont>
#include <QGraphicsAnchorLayout>
#include <QGraphicsSimpleTextItem>

PKeyboard::PKeyboard(CKeyboard* control)
    : PModule(control)
{
}

void PKeyboard::initialize(PVirtualPort *outputFrequency, PVirtualPort *outputGate)
{
    TextWidget* title = new TextWidget("Keys", this);
    title->setFont(QFont("Courier", 18, QFont::Bold));

    m_pKeyboardView = new PKeyboardView(this);

    // Layout
    rightArea()->addAnchors(outputFrequency, rightArea());
    // TODO : add second output.
    // bottomArea()->addAnchors(outputGate, bottomArea());

    bottomArea()->addAnchors(m_pKeyboardView, bottomArea());
    centerArea()->addAnchors(title, centerArea());
}
