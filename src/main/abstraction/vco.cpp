#include "vco.h"

#include "inport.h"
#include "outport.h"
#include "wavegenerator.h"

VCO::VCO(QObject* parent)
    : Module(parent)
    , m_waveGenerator(0)
{
    init();
}
void VCO::process()
{
    m_defaultOutPort->switchBuffers();
    m_waveGenerator->generate(m_defaultInPort->buffer(), m_defaultOutPort->buffer());
}

QList<Module*>::const_iterator VCO::getReguirements() const
{
    return 0;
}

void VCO::setWaveGenerator(WaveGenerator* waveGenerator)
{
    if (m_waveGenerator) {
        delete(m_waveGenerator);}
    m_waveGenerator = waveGenerator;
}

void VCO::init()
{
    /// Initialization of a default InPort and a default OutPort for the VCO
    m_defaultInPort = new InPort(this);
    m_defaultOutPort = new OutPort(this);
}
