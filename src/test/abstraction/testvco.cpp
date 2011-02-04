#include "testvco.h"

#include "abstraction/vco.h"
#include "abstraction/wavegeneratordummy.h"

void TestVCO::testVCO()
{
    VCO vco;
    vco.setWaveGenerator(new WaveGeneratorDummy);
    vco.process();
}
