#include "lfo.h"

#include "abstraction/component/dimmer.h"
#include "abstraction/component/inport.h"
#include "abstraction/component/outport.h"
#include "abstraction/component/selector.h"
#include "abstraction/wavegen/wavegenerator.h"
#include "factory/synthprofactory.h"
#include "factory/wavegeneratorfactory.h"

const QString LFO::SHAPE_DEFAULT = tr("Saw");

LFO::LFO(SynthPro* parent)
    : Module(parent)
    , m_waveGenerator(0)
    , m_waveGeneratorFactory(new WaveGeneratorFactory())
    , m_out(0)
    , m_shapeSelector(0)
    , m_kDimmer(0)
    , m_rangeDimmer(0)
    , m_offsetDimmer(0)
    , m_lfoBuffer(0)
{
}

void LFO::initialize(SynthProFactory* factory)
{
    m_lfoBuffer = new Buffer();

    m_out = factory->createOutPortReplicable(this, "out");
    m_outports.append(m_out);

    /// Creation of the Selector
    m_shapeSelector = factory->createSelector(m_waveGeneratorFactory->selectorConversionMap().keys(), 0,
                                              m_waveGeneratorFactory->selectorConversionMap().values(), "Wave Type", this);

    /// Connection of the Selector
    connect(m_shapeSelector, SIGNAL(choiceChanged(int)), this, SLOT(waveShapeChanged(int)));

    /// Creation of the Dimmers
    m_kDimmer = factory->createDialDimmer("K", K_MIN, K_MAX, K_DEFAULT, this);
    m_rangeDimmer = factory->createDialDimmer("Range", RANGE_MIN, RANGE_MAX, RANGE_DEFAULT, this);
    m_offsetDimmer = factory->createDialDimmer("Offset", OFFSET_MIN, OFFSET_MAX, OFFSET_DEFAULT, this);

    setShape(SHAPE_DEFAULT);
}

LFO::~LFO()
{
    if (m_waveGenerator) {
        delete m_waveGenerator;
    }

    // FIXME, this leads to an infinite loop of bad desalloc.
    delete m_lfoBuffer;
}

void LFO::ownProcess()
{
    // First step : create the "input" buffer with a constant frequency, and generate the wave.
    qreal* dataIn = m_lfoBuffer->data();
    for (int i = 0, size = m_lfoBuffer->length(); i < size; i++) {
        dataIn[i] = m_kDimmer->value();
    }

    m_waveGenerator->generate(m_lfoBuffer, m_out->buffer());

    // Second step : amplify the output and add an offset.
    qreal* m_dataOut = m_out->buffer()->data();
    for (int i = 0, size = m_out->buffer()->length(); i < size; i++) {
        m_dataOut[i] = m_dataOut[i] * m_rangeDimmer->value() + m_offsetDimmer->value();
    }
}

qreal LFO::k() const
{
    return m_kDimmer->value();
}

void LFO::setK(qreal value)
{
    m_kDimmer->setValue(value);
}

qreal LFO::range() const
{
    return m_rangeDimmer->value();
}

void LFO::setRange(qreal value)
{
    m_rangeDimmer->setValue(value);
}

qreal LFO::offset() const
{
    return m_offsetDimmer->value();
}

void LFO::setOffset(qreal value)
{
    m_offsetDimmer->setValue(value);
}

void LFO::waveShapeChanged(int selectedValue)
{
    if (m_waveGenerator) {
        delete m_waveGenerator;
    }

    QString waveType = m_waveGeneratorFactory->selectorConversionMap()[selectedValue];
    m_waveGenerator = m_waveGeneratorFactory->createWaveGenerator(waveType);
}

QString LFO::shape()
{

    return m_waveGeneratorFactory->selectorConversionMap()[m_shapeSelector->choice()];
}

void LFO::setShape(QString shape)
{
    m_shapeSelector->setChoice(m_waveGeneratorFactory->selectorConversionMap().key(shape));
}
