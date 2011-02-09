#include "cmoduleout.h"

#include "control/cinport.h"
#include "presentation/pmoduleout.h"

CModuleOut::CModuleOut(QIODevice* device, QAudioOutput* output, QObject* parent)
    : Module(parent)
    , ModuleOut(device, output, parent)
    , CModule(parent)
{
}

void CModuleOut::initialize(SynthProFactory* factory)
{
    ModuleOut::initialize(factory);

    CInPort* in = dynamic_cast<CInPort*>(m_inPort);

    dynamic_cast<PModuleOut*>(presentation())->initialize(in->presentation());
}
