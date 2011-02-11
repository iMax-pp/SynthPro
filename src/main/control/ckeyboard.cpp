#include "ckeyboard.h"

#include "control/coutport.h"
#include "presentation/pkeyboard.h"

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

    //dynamic_cast<POscilloscope*>(presentation())->setVisualizedBuffer(inports().at(0)->buffer());
}

void CKeyboard::ownProcess()
{
    //dynamic_cast<PKeyboard*>(presentation())->refreshOscilloscopeView();
}
