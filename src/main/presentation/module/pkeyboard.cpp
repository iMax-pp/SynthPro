#include "pkeyboard.h"

#include "abstraction/buffer.h"
#include "control/module/ckeyboard.h"
#include "presentation/component/pvirtualport.h"
#include "presentation/widget/pkeyboardview.h"
#include "presentation/widget/textwidget.h"

#include <QAction>
#include <QFont>
#include <QGraphicsAnchorLayout>
#include <QGraphicsSimpleTextItem>

PKeyboard::PKeyboard(CKeyboard* control)
    : PModule(control)
{
}

void PKeyboard::initialize(PVirtualPort *outputFrequency, PVirtualPort *outputGate)
{
    TextWidget* title = new TextWidget(tr("Keys"), this);
    title->setFont(QFont("Courier", 18, QFont::Bold));

    m_pKeyboardView = new PKeyboardView(this);
    connect(m_pKeyboardView, SIGNAL(keyboardKeyPressed(int)), this, SLOT(keyboardKeyPressed(int)));
    connect(m_pKeyboardView, SIGNAL(keyboardKeyReleased(int)), this, SLOT(keyboardKeyReleased(int)));

    // Layout
    rightArea()->addAnchors(outputFrequency, rightArea());
    leftArea()->addAnchors(outputGate, leftArea());

    bottomArea()->addAnchors(m_pKeyboardView, bottomArea());
    centerArea()->addAnchors(title, centerArea());

    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemAcceptsInputMethod);
    setFocus();
}

void PKeyboard::postInitialize()
{
    m_pKeyboardView->postInitialize();
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
