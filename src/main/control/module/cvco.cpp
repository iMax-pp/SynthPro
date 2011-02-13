#include "cvco.h"

#include "control/component/cdimmer.h"
#include "control/component/cinport.h"
#include "control/component/coutport.h"
#include "control/component/cselector.h"
#include "presentation/module/pvco.h"

CVCO::CVCO(SynthPro* parent)
    : Module(parent)
    , VCO(parent)
    , CModule(parent)
{
}

void CVCO::initialize(SynthProFactory* factory)
{
    VCO::initialize(factory);

    CInPort* vfm = dynamic_cast<CInPort*>(m_vfm);
    COutPort* out = dynamic_cast<COutPort*>(m_out);
    CSelector* selector = dynamic_cast<CSelector*>(m_shapeSelector);
    CDimmer* k = dynamic_cast<CDimmer*>(m_kDimmer);

    dynamic_cast<PVCO*>(presentation())->initialize(vfm->presentation(), out->presentation(),
                                                    selector->presentation(), k->presentation());
}
