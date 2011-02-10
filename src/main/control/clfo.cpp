#include "clfo.h"

#include "control/cdimmer.h"
#include "control/cinport.h"
#include "control/coutport.h"
#include "control/cselector.h"
#include "presentation/plfo.h"

CLFO::CLFO(SynthPro* parent)
    : Module(parent)
    , LFO(parent)
    , CModule(parent)
{
}

void CLFO::initialize(SynthProFactory* factory)
{
    LFO::initialize(factory);

    COutPort* output = dynamic_cast<COutPort*>(m_out);
    CSelector* selector = dynamic_cast<CSelector*>(m_shapeSelector);
    CDimmer* k = dynamic_cast<CDimmer*>(m_kDimmer);
    CDimmer* range = dynamic_cast<CDimmer*>(m_rangeDimmer);
    CDimmer* offset= dynamic_cast<CDimmer*>(m_offsetDimmer);

    dynamic_cast<PLFO*>(presentation())->initialize(output->presentation(), k->presentation(),
                                                    range->presentation(), offset->presentation(),
                                                    selector->presentation());
}
