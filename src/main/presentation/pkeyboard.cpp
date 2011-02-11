#include "pkeyboard.h"

#include "abstraction/buffer.h"
#include "control/ckeyboard.h"
#include "presentation/pkeyboardview.h"
#include "presentation/pvirtualport.h"
#include "presentation/textwidget.h"

#include <QDebug>
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
    connect(m_pKeyboardView, SIGNAL(keyboardKeyPressed(int)), this, SLOT(keyboardKeyPressed(int)));
    connect(m_pKeyboardView, SIGNAL(keyboardKeyReleased(int)), this, SLOT(keyboardKeyReleased(int)));

    // Layout
    rightArea()->addAnchors(outputFrequency, rightArea());
    leftArea()->addAnchors(outputGate, leftArea());

    bottomArea()->addAnchors(m_pKeyboardView, bottomArea());
    centerArea()->addAnchors(title, centerArea());
}

void PKeyboard::keyboardKeyPressed(int keyPressed)
{
    CKeyboard* control = dynamic_cast<CKeyboard*>(m_control);
    control->keyboardKeyPressed(keyPressed);
}

void PKeyboard::keyboardKeyReleased(int keyPressed)
{
    CKeyboard* control = dynamic_cast<CKeyboard*>(m_control);
    control->keyboardKeyReleased(keyPressed);
}
