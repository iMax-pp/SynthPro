#include "ckeyboard.h"

#include "control/coutport.h"
#include "presentation/pkeyboard.h"

#include <QDebug>

CKeyboard::CKeyboard(SynthPro* parent)
    : Module(parent)
    , ModuleKeyboard(parent)
    , CModule(parent)
{
}

void CKeyboard::initialize(SynthProFactory* factory)
{
    ModuleKeyboard::initialize(factory);

    COutPort* outFrequency = dynamic_cast<COutPort*>(m_outPortFrequency);
    COutPort* outGate = dynamic_cast<COutPort*>(m_outPortGate);

    dynamic_cast<PKeyboard*>(presentation())->initialize(outFrequency->presentation(),
                                                         outGate->presentation());
}

void CKeyboard::ownProcess()
{
}

void CKeyboard::keyboardKeyPressed(int keyPressed)
{
    m_keyPressedNumber = keyPressed;
    m_pressed = true;
}

void CKeyboard::keyboardKeyReleased(int keyPressed)
{
    m_pressed = false;
}
