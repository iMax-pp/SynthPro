#include "testdelay.h"

#include "abstraction/buffer.h"
#include "abstraction/component/connection.h"
#include "abstraction/component/inport.h"
#include "abstraction/component/outport.h"
#include "abstraction/module/vco.h"
#include "abstraction/synthpro.h"
#include "factory/simplefactory.h"

#include <QDebug>


void TestDelay::testDelay()
{
    qDebug() << "debut du test";

    SimpleFactory factory;
    SynthPro* synth = factory.createSynthPro();
    Delay* delay = factory.createDelay(synth);
    VCO* vco = factory.createVCO(synth);
    vco->outports().first()->connect(delay->inports().first());
    int nbValues = 10;
    int nbEcho = 0;

    // put 1 in the buffer
    for (int i = 0 ; i <  nbValues ; i++) {
        vco->outports().first()->buffer()->data()[i] = 1;
    }
    for (int j = 0 ; j < 4500 ; j++) {
        delay->process();
        for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; i++) {
            vco->outports().first()->buffer()->data()[i] = 0;
        }
        // read the echo
        for (int k = 0 ; k < Buffer::DEFAULT_LENGTH ; k++) {
            if (delay->outports().first()->buffer()->data()[k] != 0) {
                nbEcho++;
            }
        }
    }
    qDebug() << nbValues << " " << nbEcho;
    QVERIFY(nbEcho == nbValues*4);
    delete delay;
    delete synth;
}
