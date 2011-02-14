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
    , m_mapKeyboard(0)
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

    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemAcceptsInputMethod);
    setFocus();

    // Keyboard management (trigger notes with the computer keyboard).
    int val = 0; // First key.
    m_mapKeyboard = new QMap<int, int>();
    m_mapKeyboard->insert(Qt::Key_Q, val++);
    m_mapKeyboard->insert(Qt::Key_Z, val++);
    m_mapKeyboard->insert(Qt::Key_S, val++);
    m_mapKeyboard->insert(Qt::Key_E, val++);
    m_mapKeyboard->insert(Qt::Key_D, val++);
    m_mapKeyboard->insert(Qt::Key_F, val++);
    m_mapKeyboard->insert(Qt::Key_T, val++);
    m_mapKeyboard->insert(Qt::Key_G, val++);
    m_mapKeyboard->insert(Qt::Key_Y, val++);
    m_mapKeyboard->insert(Qt::Key_H, val++);
    m_mapKeyboard->insert(Qt::Key_U, val++);
    m_mapKeyboard->insert(Qt::Key_J, val++);
    m_mapKeyboard->insert(Qt::Key_K, val++);
}

void PKeyboard::postInitialize()
{
    grabKeyboard();
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

void PKeyboard::keyPressEvent(QKeyEvent* event)
{
    int key = event->key();
    if (m_mapKeyboard->contains(key)) {
        keyboardKeyPressed(m_mapKeyboard->value(key));
    }
}

void PKeyboard::keyReleaseEvent(QKeyEvent* event)
{
    int key = event->key();
    if (m_mapKeyboard->contains(key)) {
        keyboardKeyReleased(m_mapKeyboard->value(key));
    }
}
