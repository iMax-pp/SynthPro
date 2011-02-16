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

    Keyboard* keyboard = factory.createKeyboard(synth);
    VCO* vco = factory.createVCO(synth);
    vco->outports().first()->connect(sampler->inports().first());
    keyboard->outports().at(1)->connect(sampler->inports().at(1));

    // initialization of the gate port
    for (int i = 0 ; i < 10 ; ++i){
      //  sampler->inports().at(1)->buffer()->data()[i] = 10;
        keyboard->outports().at(1)->buffer()->data()[i] = 0;
    }

    for (int i = 10 ; i < 100 ; ++i){
       // sampler->inports().at(1)->buffer()->data()[i] = 10;
        keyboard->outports().at(1)->buffer()->data()[i] = 10;

    }
    for (int i = 100 ; i < 200 ; ++i){
       // sampler->inports().at(1)->buffer()->data()[i] = 10;
        keyboard->outports().at(1)->buffer()->data()[i] = 0;
    }
    for (int i = 200 ; i < 300 ; ++i){
       // sampler->inports().at(1)->buffer()->data()[i] = 10;
        keyboard->outports().at(1)->buffer()->data()[i] = 10;
    }
    for (int i = 300 ; i < 400 ; ++i){
       // sampler->inports().at(1)->buffer()->data()[i] = 10;
        keyboard->outports().at(1)->buffer()->data()[i] = 0;
    }
    for (int i = 400 ; i < 500 ; ++i){
       // sampler->inports().at(1)->buffer()->data()[i] = 10;
        keyboard->outports().at(1)->buffer()->data()[i] = 0;
    }
    for (int i = 500 ; i < 600 ; ++i){
       // sampler->inports().at(1)->buffer()->data()[i] = 10;
        keyboard->outports().at(1)->buffer()->data()[i] = 10;
    }
    // initialization of the vco outport
    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; i++) {
        vco->outports().first()->buffer()->data()[i] = 5;
    }
    vco->process();
    sampler->process();
    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; i++) {
        qDebug() << "out : " << sampler->outports().at(0)->buffer()->data()[i];

    }



}
