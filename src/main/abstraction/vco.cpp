#include "vco.h"

VCO::VCO(QObject* parent)
    : Module(parent)
{
}
void VCO::process(){

}

QList<Module*>::const_iterator VCO::getReguirements() const {
    return 0;
}

void VCO::setWaveGenerator(WaveGenerator* waveGenerator){
    m_waveGenerator = waveGenerator ;
}
