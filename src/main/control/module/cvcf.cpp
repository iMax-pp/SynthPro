#include "cvcf.h"

#include "abstraction/filter/filterhp229.h"
#include "abstraction/filter/filterlp229.h"
#include "abstraction/module/vco.h"
#include "control/component/cdimmer.h"
#include "control/component/cinport.h"
#include "control/component/coutport.h"
#include "control/component/cselector.h"
#include "factory/filterfactory.h"
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

    resonance->setValueFormat(formatResonance);

    dynamic_cast<PVCF*>(presentation())->initialize(in->presentation(), cutOff ->presentation(),
                                                    out->presentation(), selector->presentation(),
                                                    resonance->presentation(), cutOffDimmer->presentation());
}

void CVCF::filterChanged(int selectedValue)
{
    VCF::filterChanged(selectedValue);
    QString filterId = m_filterFactory->selectorConversionMap()[selectedValue];
    CDimmer* cutOff = dynamic_cast<CDimmer*>(m_cutOffDimmer);
    if (filterId == FilterFactory::LowPass) {
        cutOff->setValueFormat(formatLPCutOff);
    } else if (filterId == FilterFactory::HighPass) {
        cutOff->setValueFormat(formatHPCutOff);
    } else {
        cutOff->setValueFormat(formatEmpty);
    }
}

QString CVCF::formatHPCutOff(qreal cutOff)
{
    long f = (cutOff - CUT_OFF_MIN)
             * (FilterHP229::MAX_FREQUENCY - FilterHP229::MIN_FREQUENCY)
             / (CUT_OFF_MAX - CUT_OFF_MIN)
             + FilterHP229::MIN_FREQUENCY;
    return QString::number(f) + " Hz";
}

QString CVCF::formatLPCutOff(qreal cutOff)
{
    long f = (cutOff - CUT_OFF_MIN)
             * (FilterLP229::MAX_FREQUENCY - FilterLP229::MIN_FREQUENCY)
             / (CUT_OFF_MAX - CUT_OFF_MIN)
             + FilterLP229::MIN_FREQUENCY;
    return QString::number(f) + " Hz";
}

QString CVCF::formatEmpty(qreal)
{
    return QString();
}

QString CVCF::formatResonance(qreal res)
{
    return QString::number(res, 'g', 2);
}
