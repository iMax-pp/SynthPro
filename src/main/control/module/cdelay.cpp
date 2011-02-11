#include "cdelay.h"

#include "control/cdimmer.h"
#include "control/cinport.h"
#include "control/coutport.h"
#include "presentation/module/pdelay.h"

CDelay::CDelay(SynthPro* parent)
    : Module(parent)
    , Delay(parent)
    , CModule(parent)
{
}

void CDelay::initialize(SynthProFactory* factory)
{
    Delay::initialize(factory);

    CInPort* in = dynamic_cast<CInPort*>(m_inPort);
    COutPort* out = dynamic_cast<COutPort*>(m_outPort);
    CDimmer* duration = dynamic_cast<CDimmer*>(m_durationDimmer);
    CDimmer* decay = dynamic_cast<CDimmer*>(m_decayDimmer);

    dynamic_cast<PDelay*>(presentation())->initialize(in->presentation(), out->presentation(),
                                                      duration->presentation(), decay->presentation());
}
