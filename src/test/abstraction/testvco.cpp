#include "testvco.h"

#include "abstraction/vco.h"
#include "abstraction/wavegeneratordummy.h"

void TestVCO::testVCO()
{
    VCO* vco = new VCO();
    vco->setWaveGenerator(new WaveGeneratorDummy());
    vco->process();
}
