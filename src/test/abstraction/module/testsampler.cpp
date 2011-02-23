#include "testsampler.h"

#include "abstraction/buffer.h"
#include "abstraction/component/inport.h"
#include "abstraction/component/outport.h"
#include "abstraction/mock/mockserializerwell.h"
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

    QString result;
    QTextStream stream(&result);
    MockSerializerWell output(0, stream, &factory);
    sampler->outports().first()->connect(&output.input);
    bool res = true;

    for (int k = 0 ; k < 10 ; k++) {
        int i = 0;
        while (i++ < Buffer::DEFAULT_LENGTH) {
            keyboard->outports().at(1)->buffer()->data()[i] = k%3;

        }
        for (int j = 0 ; j < Buffer::DEFAULT_LENGTH ; j++) {
            vco->outports().first()->buffer()->data()[j] = j;
        }
        sampler->process();
        for (int i = 0 ; i  < Buffer::DEFAULT_LENGTH ; i++) {
            switch (k) {
            case 0 :
            case 1 :
            case 3 :
            case 6 :
            case 9 : res &= sampler->outports().first()->buffer()->data()[i] == 0;
                break;
            case 2 :
            case 4 :
            case 5 :
            case 7 :
            case 8 : res &= sampler->outports().first()->buffer()->data()[i] == i;
                break;
            default :
                break;
            }
                }
        output.process();
    }
    QVERIFY(res);
}
