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

void CKeyboard::keyboardKeyPressed(int keyPressed)
{
    m_keyPressedNumber = keyPressed;
    m_pressed = true;
}

void CKeyboard::keyboardKeyReleased(int)
{
    m_pressed = false;
}
