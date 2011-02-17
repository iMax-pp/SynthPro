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
    keyboard->outports().at(1)->connect(sampler->inports().at(1));
    // qreal inValue = 5 ;
    bool res = true;
    Buffer sampledBuffer;
    for (int j = 0 ; j < 7 ; j++) {
        for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; i++) {
            if (j%2 == 0) {
                keyboard->outports().at(1)->buffer()->data()[i] = 0;
            } else {
                keyboard->outports().at(1)->buffer()->data()[i] = 1;
            }
            if (j == 1) {
                sampledBuffer.data()[i] = vco->outports().first()->buffer()->data()[i];
            }
            vco->process();
            sampler->process();
            if (j == 5) {

                // qDebug() << sampler->outports().first()->buffer()->data()[i]<< "" << sampledBuffer.data()[i];
            }
        }
    }
    QVERIFY(res);
}
