#include "cvco.h"

#include "cdimmer.h"
#include "cinport.h"
#include "coutport.h"
#include "cselector.h"
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

    CInPort* vfm = dynamic_cast<CInPort*>(m_vfm);
    COutPort* out = dynamic_cast<COutPort*>(m_out);
    CSelector* selector = dynamic_cast<CSelector*>(m_shapeSelector);
    CDimmer* dimmer = dynamic_cast<CDimmer*>(m_kDimmer);

    dynamic_cast<PVCO*>(presentation())->initialize(vfm->presentation(), out->presentation(), selector->presentation(), dimmer->presentation());
}
