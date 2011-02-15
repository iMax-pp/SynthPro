#include "cvcf.h"

#include "abstraction/module/vco.h"
#include "control/component/cdimmer.h"
#include "control/component/cinport.h"
#include "control/component/coutport.h"
#include "control/component/cselector.h"
#include "presentation/module/pvcf.h"
#include <qmath.h>

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
    CDimmer* resonance = dynamic_cast<CDimmer*>(m_rDimmer);
    CDimmer* cutOffDimmer = dynamic_cast<CDimmer*>(m_cutOffDimmer);

    cutOffDimmer->setValueFormat(formatCutOff);
    resonance->setValueFormat(formatResonance);

    dynamic_cast<PVCF*>(presentation())->initialize(in->presentation(), cutOff ->presentation(),
                                                    out->presentation(), selector->presentation(),
                                                    resonance->presentation(), cutOffDimmer->presentation());
}

QString CVCF::formatCutOff(qreal cutOff)
{
    return QString::number((long)cutOff) + " Hz"; // FIXME
}

QString CVCF::formatResonance(qreal res)
{
    return QString::number(res, 'g', 2) + " ?"; // FIXME
}
