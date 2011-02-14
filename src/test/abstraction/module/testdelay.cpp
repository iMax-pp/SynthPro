#include "testdelay.h"

#include "abstraction/buffer.h"
#include "abstraction/component/connection.h"
#include "abstraction/component/inport.h"
#include "abstraction/component/outport.h"
#include "abstraction/component/port.h"
#include "abstraction/module/vco.h"
#include "abstraction/synthpro.h"
#include "factory/simplefactory.h"

#include <QDebug>

void TestDelay::testDelay()
{


    SimpleFactory factory;
    SynthPro* synth = factory.createSynthPro();
    Delay* delay = factory.createDelay(synth);
    VCO* vco = factory.createVCO(synth);
    vco->outports().first()->connect(delay->inports().first());

    vco->setShape("Sinus");
    for (int i = 0 ; i < 1000 ; i++) {
        vco->process();
        delay->process();
    }
    /// TODO implement test !

    delete delay;
    delete synth;
}
