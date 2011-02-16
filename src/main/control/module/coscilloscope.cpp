#include "coscilloscope.h"

#include "control/component/cdimmer.h"
#include "control/component/cinport.h"
#include "control/component/cpushbutton.h"
#include "presentation/module/poscilloscope.h"

COscilloscope::COscilloscope(SynthPro* parent)
    : Module(parent)
    , Oscilloscope(parent)
    , CModule(parent)
{
}

void COscilloscope::initialize(SynthProFactory* factory)
{
    Oscilloscope::initialize(factory);

    CInPort* in = dynamic_cast<CInPort*>(m_inPort);
    CPushButton* stabilizeButton = dynamic_cast<CPushButton*>(m_stabilizeControl);

    dynamic_cast<POscilloscope*>(presentation())->initialize(in->presentation(), stabilizeButton->presentation());

    dynamic_cast<POscilloscope*>(presentation())->setVisualizedBuffer(inports().at(0)->buffer());
}

void COscilloscope::ownProcess()
{
    dynamic_cast<POscilloscope*>(presentation())->refreshOscilloscopeView();
}
