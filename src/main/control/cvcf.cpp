#include "cvcf.h"

#include "cdimmer.h"
#include "cinport.h"
#include "coutport.h"
#include "cselector.h"
#include "presentation/pvcf.h"

CVCF::CVCF(QObject* parent)
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
    CDimmer* dimmer = dynamic_cast<CDimmer*>(m_rDimmer);

    dynamic_cast<PVCF*>(presentation())->initialize(in->presentation(), cutOff ->presentation(),
                                                    out->presentation(), selector->presentation(), dimmer->presentation());
}
