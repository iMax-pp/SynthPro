#include "cvca.h"

#include "control/component/cdimmer.h"
#include "control/component/cinport.h"
#include "control/component/coutport.h"
#include "control/component/cselector.h"
#include "presentation/module/pvca.h"

CVCA::CVCA(SynthPro* parent)
    : Module(parent)
    , VCA(parent)
    , CModule(parent)
{
}

void CVCA::initialize(SynthProFactory* factory)
{
    VCA::initialize(factory);

    CInPort* in = dynamic_cast<CInPort*>(m_inPort);
    COutPort* out = dynamic_cast<COutPort*>(m_outPort);
    CInPort* controlInput = dynamic_cast<CInPort*>(m_controlInput);
    CDimmer* dimmer = dynamic_cast<CDimmer*>(m_gainDimmer);

    dynamic_cast<PVCA*>(presentation())->initialize(in->presentation(), out->presentation(),
                                                    controlInput->presentation(), dimmer->presentation());
}
