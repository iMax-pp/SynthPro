#include "vco.h"

#include "abstraction/dimmer.h"
#include "abstraction/inport.h"
#include "abstraction/outport.h"
#include "abstraction/selector.h"
#include "abstraction/wavegenerator.h"
#include "factory/synthprofactory.h"


VCO::VCO(SynthProFactory* factory, QObject* parent)
VCO::VCO(QObject* parent)
    : Module(parent)
    , m_waveGenerator(0)
    , m_vfm(0)
    , m_out(0)
    , m_shapeSelector(0)
    , m_kDimmer(0)
{
}

void VCO::initialize(SynthProFactory* factory)
{
    qDebug("VCO::init Creation of vfm port in the VCO");
    m_vfm = factory->createInPortReplicable(this);
    m_inports.append(m_vfm);

    qDebug("VCO::init Creation of out port in the VCO");
    m_out = factory->createOutPortReplicable(this);
    m_outports.append(m_out);

    m_kDimmer = factory->createKDimmer(K_MIN, K_MAX, K_DEFAULT, this);
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

void VCO::setWaveGenerator(WaveGenerator* waveGenerator)
{
    if (m_waveGenerator) {
        delete m_waveGenerator;
    }

    m_waveGenerator = waveGenerator;
}

Dimmer* VCO::dimmer()
{
    return m_kDimmer;
}
