#include "coscilloscope.h"

#include "control/cdimmer.h"
#include "control/cinport.h"
#include "presentation/poscilloscope.h"

COscilloscope::COscilloscope(SynthPro* parent)
    : Module(parent)
    , ModuleOscilloscope(parent)
    , CModule(parent)
{
}

void COscilloscope::initialize(SynthProFactory* factory)
{
    ModuleOscilloscope::initialize(factory);

    CInPort* in = dynamic_cast<CInPort*>(m_inPort);

    dynamic_cast<POscilloscope*>(presentation())->initialize(in->presentation());

    dynamic_cast<POscilloscope*>(presentation())->setVisualizedBuffer(inports().at(0)->buffer());
}

void COscilloscope::ownProcess()
{
    dynamic_cast<POscilloscope*>(presentation())->refreshOscilloscopeView();
}
