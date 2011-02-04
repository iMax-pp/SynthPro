#include "vco.h"

#include "inport.h"
#include "outport.h"
#include "wavegenerator.h"

VCO::VCO(QObject* parent)
    : Module(parent)
    , m_waveGenerator(0)
    , m_vfm(this)
    , m_out(this)
{
    m_inports.append(&m_vfm);
    m_outports.append(&m_out);
    init();
}

VCO::~VCO()
{
    if (m_waveGenerator) {
        delete m_waveGenerator;
    }
}

void VCO::process()
{
    m_out.switchBuffers();
    m_waveGenerator->generate(m_vfm.buffer(), m_out.buffer());
}

void VCO::setWaveGenerator(WaveGenerator* waveGenerator)
{
    if (m_waveGenerator) {
        delete m_waveGenerator;
    }
    m_waveGenerator = waveGenerator;
}

void VCO::init()
{
}
