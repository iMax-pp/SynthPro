#include "vco.h"

#include "inport.h"
#include "outport.h"

VCO::VCO(QObject* parent)
    : Module(parent)
    , m_waveGenerator(0)
{
}
void VCO::process()
{

}

QList<Module*>::const_iterator VCO::getReguirements() const
{
    return 0;
}

void VCO::setWaveGenerator(WaveGenerator* waveGenerator)
{
    m_waveGenerator = waveGenerator;
}

void VCO::init()
{
    /// Initialization of a default InPort and a default OutPort for the VCO
    m_defaultInPort = new InPort(this);
    m_defaultOutPort = new OutPort(this);
}
