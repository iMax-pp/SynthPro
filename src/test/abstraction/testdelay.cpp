#include "testdelay.h"

#include "QDebug"

#include "abstraction/buffer.h"
#include "abstraction/inport.h"
#include "abstraction/outport.h"
#include "abstraction/port.h"
#include "abstraction/synthpro.h"
#include "abstraction/vco.h"

#include "factory/simplefactory.h"

void TestDelay::testDelay()
{
    SimpleFactory factory;
    SynthPro* synth = factory.createSynthPro();
    Delay* delay = factory.createDelay(synth);
    VCO* vco = factory.createVCO(synth);
    vco->outports().first()->connections().first()->connect(delay->inports().first()->connections().first());
    qDebug() << tr("là ça passe !");

    for (int i = 0 ; i < 1000 ; i++) {
        // vco->process();
        delay->process();
    }



}
