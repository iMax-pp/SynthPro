#include "cvcf.h"

#include "control/cdimmer.h"
#include "control/cinport.h"
#include "control/coutport.h"
#include "control/cselector.h"
#include "presentation/pvcf.h"

CVCF::CVCF(SynthPro* parent)
    : Module(parent)
    , VCF(parent)
    , CModule(parent)
{
}

void CVCF::initialize(SynthProFactory* factory)
{
    VCF::initialize(factory);

    CInPort* in = dynamic_cast<CInPort*>(m_inPort);
    CInPort* cutOff = dynamic_cast<CInPort*>(m_inCutOffPort);
    COutPort* out = dynamic_cast<COutPort*>(m_out);
    CSelector* selector = dynamic_cast<CSelector*>(m_filterSelector);
    CDimmer* rDimmer = dynamic_cast<CDimmer*>(m_rDimmer);
    CDimmer* cutOffDimmer = dynamic_cast<CDimmer*>(m_cutOffDimmer);

    dynamic_cast<PVCF*>(presentation())->initialize(in->presentation(), cutOff ->presentation(),
                                                    out->presentation(), selector->presentation(),
                                                    rDimmer->presentation(), cutOffDimmer->presentation());
}
