#include "testsampler.h"

#include "abstraction/buffer.h"
#include "abstraction/component/inport.h"
#include "abstraction/component/outport.h"
#include "abstraction/module/keyboard.h"
#include "abstraction/module/vco.h"
#include "factory/simplefactory.h"

#include <QDebug>

void TestSampler::testSampler()
{
    SimpleFactory factory;
    SynthPro* synth = factory.createSynthPro();
    Sampler* sampler = factory.createSampler(synth);

    VCO* vco = factory.createVCO(synth);
    vco->outports().first()->connect(sampler->inports().first());


    // initialization of the gate port
    for (int i = 0 ; i < 10 ; ++i){
        sampler->inports().at(1)->buffer()->data()[i] = 10;
    }

    for (int i = 10 ; i < Buffer::DEFAULT_LENGTH ; ++i){
        sampler->inports().at(1)->buffer()->data()[i] = 10;
    }
    // initialization of the vco outport
    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; i++) {
        vco->outports().first()->buffer()->data()[i] = 5;
    }
    sampler->process();
    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; i++) {
        if (i%100){
   //         qDebug() << "gate : " << sampler->inports().at(1)->buffer()->data()[i];
        }
    }



}
