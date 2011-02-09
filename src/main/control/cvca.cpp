#include "cvca.h"

#include "cdimmer.h"
#include "cinport.h"
#include "coutport.h"
#include "cselector.h"
#include "presentation/pvca.h"

CVCA::CVCA(QObject* parent)
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
    CDimmer* dimmer = dynamic_cast<CDimmer*>(m_gainDimmer);

    dynamic_cast<PVCA*>(presentation())->initialize(in->presentation(), out->presentation(), dimmer->presentation());
}
