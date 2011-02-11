#include "cspeaker.h"

#include "control/cinport.h"
#include "presentation/module/pspeaker.h"

CSpeaker::CSpeaker(SynthPro* parent, QIODevice* device, QAudioOutput* output)
    : Module(parent)
    , Speaker(parent, device, output)
    , CModule(parent)
{
}

void CSpeaker::initialize(SynthProFactory* factory)
{
    Speaker::initialize(factory);

    CInPort* in = dynamic_cast<CInPort*>(m_inPort);

    dynamic_cast<PSpeaker*>(presentation())->initialize(in->presentation());
}
