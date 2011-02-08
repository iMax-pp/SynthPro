#include "cvco.h"

#include "control/cdimmer.h"
#include "control/cinport.h"
#include "control/coutport.h"
#include "presentation/pvco.h"

CVCO::CVCO(QObject* parent)
    : Module(parent)
    , VCO(parent)
    , CModule(parent)
{
}

void CVCO::initialize(SynthProFactory* factory)
{
    VCO::initialize(factory);

    CInPort* in = dynamic_cast<CInPort*>(m_vfm);
    COutPort* out = dynamic_cast<COutPort*>(m_out);
    CDimmer* dimmer = dynamic_cast<CDimmer*>(m_kDimmer);

    dynamic_cast<PVCO*>(presentation())->initialize(in->presentation(), out->presentation(), dimmer->presentation());
}
