#include "vco.h"

#include "abstraction/dimmer.h"
#include "abstraction/inport.h"
#include "abstraction/outport.h"
#include "abstraction/selector.h"
#include "abstraction/wavegenerator.h"
#include "factory/synthprofactory.h"
#include "factory/wavegeneratorfactory.h"

#include <QDebug>


VCO::VCO(QObject* parent)
    : Module(parent)
    , m_waveGenerator(0)
    , m_vfm(0)
    , m_out(0)
    , m_shapeSelector(0)
    , m_kDimmer(0)
    , m_waveGeneratorFactory(new WaveGeneratorFactory())
{
}

void VCO::initialize(SynthProFactory* factory)
{
    qDebug("VCO::init Creation of vfm port in the VCO");
    m_vfm = factory->createInPortReplicable(this, "vfm");
    m_inports.append(m_vfm);

    qDebug("VCO::init Creation of out port in the VCO");
    m_out = factory->createOutPortReplicable(this, "out");
    m_outports.append(m_out);

    /// Creation of the Selector
    m_selectorConversionMap = m_waveGeneratorFactory->selectorConversionmap();
    m_selectorValueList = m_selectorConversionMap->keys();
    m_shapeSelector = factory->createSelector(&m_selectorValueList, 0, this);

    /// Connection of the Selector
    connect(m_shapeSelector, SIGNAL(choiceChanged(int)), this, SLOT(waveShapeChanged(int)));

    /// Creation of the Dimmer
    m_kDimmer = factory->createDimmer(K_MIN, K_MAX, K_DEFAULT, this);


}

VCO::~VCO()
{
    if (m_waveGenerator) {
        delete m_waveGenerator;
    }
}

void VCO::ownProcess()
{
    m_vfm->buffer()->add(m_kDimmer->value());
    m_out->swapBuffers();
    m_waveGenerator->generate(m_vfm->buffer(), m_out->buffer());
}
/**
*   DEPRECATED : it's now the WaveGeneratorFactory who instantiate the wave generator
*/
void VCO::setWaveGenerator(WaveGenerator* waveGenerator)
{
    if (m_waveGenerator) {
        delete m_waveGenerator;
    }

    m_waveGenerator = waveGenerator;
}


qreal VCO::k() const
{
    return m_kDimmer->value();
}

void VCO::setK(qreal value)
{
    m_kDimmer->setValue(value);
}

void VCO::waveShapeChanged(int selectedValue)
{
    if (m_waveGenerator) {
        delete m_waveGenerator;
    }
    m_waveGenerator = m_waveGeneratorFactory->getWaveGenerator(m_waveGeneratorFactory->selectorConversionmap()->value(selectedValue));
}

WaveGeneratorFactory::WaveType VCO::shape()
{

    return m_selectorConversionMap->value(m_shapeSelector->choice());
}

void VCO::setShape(WaveGeneratorFactory::WaveType shape)
{
    m_shapeSelector->setChoice(m_selectorConversionMap->key(shape));
}
