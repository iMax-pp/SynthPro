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
    // qreal inValue = 5 ;
    bool res = true;
    Buffer sampledBuffer;

    int i = 0;
    while (i < 50) {
        keyboard->outports().at(1)->buffer()->data()[i] = 0;
        i++;
    }

    while (i < 100) {
        keyboard->outports().at(1)->buffer()->data()[i] = 1;
        i++;
    }

    while (i < 150) {
        keyboard->outports().at(1)->buffer()->data()[i] = 0;
        i++;
    }

    while (i < 200) {
        keyboard->outports().at(1)->buffer()->data()[i] = 1;
        i++;
    }

    while (i < 250) {
        keyboard->outports().at(1)->buffer()->data()[i] = 0;
        i++;
    }

    while (i < 300) {
        keyboard->outports().at(1)->buffer()->data()[i] = 1;
        i++;
    }

    while (i < 350) {
        keyboard->outports().at(1)->buffer()->data()[i] = 0;
        i++;
    }

    while (i < 400) {
        keyboard->outports().at(1)->buffer()->data()[i] = 1;
        i++;
    }
    while (i < Buffer::DEFAULT_LENGTH) {
        keyboard->outports().at(1)->buffer()->data()[i] = 1;
        i++;
    }

    for (int j = 0 ; j < Buffer::DEFAULT_LENGTH ; j++) {
        vco->outports().first()->buffer()->data()[j] = j;
    }

    sampler->process();
    output.process();





    qDebug() << result;

    // QVERIFY(res);
}
void TestSampler::setValue(Buffer* buffer, qreal value)
{
    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; i++) {
        buffer->data()[i] = value;
    }
}
