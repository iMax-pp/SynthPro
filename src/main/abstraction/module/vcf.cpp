#include "vcf.h"

#include "abstraction/dimmer.h"
#include "abstraction/filter/filter.h"
#include "abstraction/inport.h"
#include "abstraction/outport.h"
#include "abstraction/selector.h"
#include "factory/filterfactory.h"
#include "factory/synthprofactory.h"

#include <QDebug>

VCF::VCF(SynthPro* parent)
    : Module(parent)
    , m_filter(0)
    , m_filterFactory(new FilterFactory())
    , m_inPort(0)
    , m_inCutOffPort(0)
    , m_out(0)
    , m_filterSelector(0)
    , m_rDimmer(0)
{
}

void VCF::initialize(SynthProFactory* factory)
{
    // qDebug("VCF::init Creation of in port in the VCF");
    m_inPort = factory->createInPortReplicable(this, "in");
    m_inports.append(m_inPort);

    // qDebug("VCF::init Creation of inCutOff port in the VCF");
    m_inCutOffPort = factory->createInPortReplicable(this, "in Cutoff");
    m_inports.append(m_inCutOffPort);

    // qDebug("VCF::init Creation of out port in the VCF");
    m_out = factory->createOutPortReplicable(this, "out");
    m_outports.append(m_out);

    /// Creation of the Selector
    m_filterSelector = factory->createSelector(m_filterFactory->selectorConversionMap().keys(), 0,
                                               m_filterFactory->selectorConversionMap().values(), "Filter Type", this);

    /// Connection of the Selector
    connect(m_filterSelector, SIGNAL(choiceChanged(int)), this, SLOT(filterChanged(int)));

    /// Creation of the Dimmer
    m_rDimmer = factory->createDimmer("Resonance", R_MIN, R_MAX, R_DEFAULT, this);

    /// Creation of the CutOff Dimmer
    m_cutOffDimmer = factory->createDimmer("CutOff", CUT_OFF_MIN, CUT_OFF_MAX, CUT_OFF_DEFAULT, this);

    setFilter("FilterLP229");
}

VCF::~VCF()
{
    if (m_filter) {
        delete m_filter;
    }
}

void VCF::ownProcess()
{
    // m_vfm->buffer()->add(m_rDimmer->value());
    // m_out->swapBuffers();
    // m_waveGenerator->generate(m_vfm->buffer(), m_out->buffer());
    m_filter->apply(m_inPort->buffer(), m_inCutOffPort->buffer(), m_cutOffDimmer->value(), m_rDimmer->value(), m_out->buffer());
}

/*
 * DEPRECATED
 */
void VCF::setFilter(Filter* filter)
{
    if (m_filter) {
        delete m_filter;
    }

    m_filter = filter;
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
    if (m_filter) {
        delete m_filter;
    }

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
