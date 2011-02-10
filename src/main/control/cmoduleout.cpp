#include "cmoduleout.h"

#include "control/cinport.h"
#include "presentation/pmoduleout.h"

CModuleOut::CModuleOut(SynthPro* parent, QIODevice* device, QAudioOutput* output)
    : Module(parent)
    , ModuleOut(parent, device, output)
    , CModule(parent)
{
}

void CModuleOut::initialize(SynthProFactory* factory)
{
    ModuleOut::initialize(factory);

    CInPort* in = dynamic_cast<CInPort*>(m_inPort);

    dynamic_cast<PModuleOut*>(presentation())->initialize(in->presentation());
}
