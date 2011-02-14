#include "testdelay.h"

#include "abstraction/buffer.h"
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
    vco->outports().first()->connections().first()->connect(delay->inports().first()->connections().first());

    // vco->setShape("Sinus");
    // put 1 in the buffer
    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; i++) {
        vco->outports().first()->buffer()[i] = 0;
    }
    for (int j ; j < 3000 ; j++) {
        delay->process();
        for (int i = 0 ; i < 20 ; i++) {
            vco->outports().first()->buffer()[i] = 0;
        }

        delay->process();
        for (int k = 0 ; k < Buffer::DEFAULT_LENGTH ; k++) {
            if (delay->outports().first()->buffer()[k] != 0) {
                qDebug(k);
            }
        }
    }

    delete delay;
    delete synth;
}
