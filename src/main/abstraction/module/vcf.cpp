#include "vcf.h"

#include "abstraction/component/dimmer.h"
#include "abstraction/component/inport.h"
#include "abstraction/component/outport.h"
#include "abstraction/component/selector.h"
#include "abstraction/filter/filter.h"
#include "factory/filterfactory.h"
#include "factory/synthprofactory.h"

VCF::VCF(SynthPro* parent)
    : Module(parent)
    , m_filter(0)
    , m_filterFactory(new FilterFactory())
    , m_inPort(0)
    , m_inCutOffPort(0)
    , m_out(0)
    , m_filterSelector(0)
    , m_rDimmer(0)
    , m_cutOffDimmer(0)
{
}

void VCF::initialize(SynthProFactory* factory)
{
    m_inPort = factory->createInPortReplicable(this, tr("in"));
    m_inports.append(m_inPort);

    m_inCutOffPort = factory->createInPortReplicable(this, tr("in Cutoff"));
    m_inports.append(m_inCutOffPort);

    m_out = factory->createOutPortReplicable(this, tr("out"));
    m_outports.append(m_out);

    // Creation of the Selector
    m_filterSelector = factory->createSelector(m_filterFactory->selectorConversionMap().keys(), 0,
                                               m_filterFactory->selectorConversionMap().values(), "Filter Type", this);

    // Connection of the Selector
    connect(m_filterSelector, SIGNAL(choiceChanged(int)), this, SLOT(filterChanged(int)));

    // Creation of the Dimmer
    m_rDimmer = factory->createDialDimmer(tr("Res"), R_MIN, R_MAX, R_DEFAULT, this);

    // Creation of the CutOff Dimmer
    m_cutOffDimmer = factory->createDialDimmer(tr("Cut"), CUT_OFF_MIN, CUT_OFF_MAX, CUT_OFF_DEFAULT, this);

    setFilter(FilterFactory::LowPass);
}

VCF::~VCF()
{
    delete m_filter;
}

void VCF::ownProcess()
{
    m_filter->apply(m_inPort->buffer(), m_inCutOffPort->buffer(), m_cutOffDimmer->value(), m_rDimmer->value(), m_out->buffer());
}

qreal VCF::resonance() const
{
    return m_rDimmer->value();
}

void VCF::setResonance(qreal value)
{
    m_rDimmer->setValue(value);
}

void VCF::filterChanged(int selectedValue)
{
    delete m_filter;
    m_filter = 0;

    QString filterType = m_filterFactory->selectorConversionMap()[selectedValue];
    m_filter = m_filterFactory->createFilter(filterType);
}

QString VCF::filter()
{
    return m_filterFactory->selectorConversionMap()[m_filterSelector->choice()];
}

void VCF::setFilter(QString filter)
{
    m_filterSelector->setChoice(m_filterFactory->selectorConversionMap().key(filter));
}
