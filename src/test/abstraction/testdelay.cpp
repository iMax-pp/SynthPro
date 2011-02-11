#include "testdelay.h"

#include "abstraction/module/vco.h"
#include "abstraction/synthpro.h"

#include "factory/simplefactory.h"

void TestDelay::testDelay()
{
    SimpleFactory factory;
    SynthPro* synth = factory.createSynthPro();
    Delay* delay = factory.createDelay(synth);
    VCO* vco = factory.createVCO(synth);




}
