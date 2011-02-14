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
    m_mapKeyboard->insert(grabShortcut(QKeySequence(tr("q"))), val++);
    m_mapKeyboard->insert(grabShortcut(QKeySequence(tr("z"))), val++);
    m_mapKeyboard->insert(grabShortcut(QKeySequence(tr("s"))), val++);
    m_mapKeyboard->insert(grabShortcut(QKeySequence(tr("e"))), val++);
    m_mapKeyboard->insert(grabShortcut(QKeySequence(tr("d"))), val++);
    m_mapKeyboard->insert(grabShortcut(QKeySequence(tr("f"))), val++);
    m_mapKeyboard->insert(grabShortcut(QKeySequence(tr("t"))), val++);
    m_mapKeyboard->insert(grabShortcut(QKeySequence(tr("g"))), val++);
    m_mapKeyboard->insert(grabShortcut(QKeySequence(tr("y"))), val++);
    m_mapKeyboard->insert(grabShortcut(QKeySequence(tr("h"))), val++);
    m_mapKeyboard->insert(grabShortcut(QKeySequence(tr("u"))), val++);
    m_mapKeyboard->insert(grabShortcut(QKeySequence(tr("j"))), val++);
    m_mapKeyboard->insert(grabShortcut(QKeySequence(tr("k"))), val++);
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

bool PKeyboard::event(QEvent* event)
{
    PModule::event(event);

    if (event->type() == QEvent::Shortcut) {
        QShortcutEvent* shortCut = dynamic_cast<QShortcutEvent*>(event);
        int shortCutId = shortCut->shortcutId();
        if (m_mapKeyboard->contains(shortCutId)) {
            CKeyboard* control = dynamic_cast<CKeyboard*>(m_control);
            control->keyboardKeyPressed(m_mapKeyboard->value(shortCutId));
            return true;
        }
    }
    return false;
}
