#include "testsampler.h"

#include "abstraction/buffer.h"
#include "abstraction/component/inport.h"
#include "abstraction/component/outport.h"
#include "abstraction/module/keyboard.h"
#include "abstraction/module/speaker.h"
#include "abstraction/module/vco.h"
#include "factory/simplefactory.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>


void TestSampler::testSampler()
{
    SimpleFactory factory;
    SynthPro* synth = factory.createSynthPro();
    Sampler* sampler = factory.createSampler(synth);
    Keyboard* keyboard = factory.createKeyboard(synth);
    VCO* vco = factory.createVCO(synth);
    vco->outports().first()->connect(sampler->inports().first());
    sampler->outports().first()->connect(speaker->inports().first());


    for (int j = 0 ; j < 7 ; j++) {
        for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; i++) {
            if (j%2 == 0) {
                keyboard->outports().at(1)->buffer()->data()[i] = 0;
            } else {
                keyboard->outports().at(1)->buffer()->data()[i] = 1;
            }
            if (j < 5) {
                vco->outports().first()->buffer()->data()[i] = 5;
            }
            sampler->process();
            if (j == 6) {
                qDebug() << sampler->outports().first()->buffer()->data()[i];
            }
        }
    }
}
