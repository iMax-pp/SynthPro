#include "testdelay.h"

#include "abstraction/synthpro.h"
#include "factory/simplefactory.h"

TestDelay::testDelay()
{
    SimpleFactory factory;
    SynthPro* synth = factory.createSynthPro();


}
