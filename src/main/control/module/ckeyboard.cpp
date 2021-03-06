#include "ckeyboard.h"

#include "control/component/coutport.h"
#include "presentation/module/pkeyboard.h"

CKeyboard::CKeyboard(SynthPro* parent)
    : Module(parent)
    , Keyboard(parent)
    , CModule(parent)
{
}

void CKeyboard::initialize(SynthProFactory* factory)
{
    Keyboard::initialize(factory);

    COutPort* outFrequency = dynamic_cast<COutPort*>(m_outPortFrequency);
    COutPort* outGate = dynamic_cast<COutPort*>(m_outPortGate);

    dynamic_cast<PKeyboard*>(presentation())->initialize(outFrequency->presentation(),
                                                         outGate->presentation());
}

void CKeyboard::postInitialize()
{
    dynamic_cast<PKeyboard*>(presentation())->postInitialize();
}

void CKeyboard::keyboardKeyPressed(int keyPressed)
{
    m_keyPressedNumber = keyPressed;
    m_pressed = true;
}

void CKeyboard::keyboardKeyReleased(int)
{
    m_pressed = false;
}

QString CKeyboard::settings() const
{
    // Default implementation returns an empty string.
    return "";
}

void CKeyboard::setUpSettings(const QString&)
{
    // Default implementation do nothing (no settings to set up).
}
