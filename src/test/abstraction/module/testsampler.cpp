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

    for (int k = 0 ; k < 10 ; k++) {
        int i = 0;
        while (i++ < Buffer::DEFAULT_LENGTH) {
            keyboard->outports().at(1)->buffer()->data()[i] = k%3;

        }
        for (int j = 0 ; j < Buffer::DEFAULT_LENGTH ; j++) {
            vco->outports().first()->buffer()->data()[j] = 10000 + j;
        }
        qDebug() << sampler->state();
        sampler->process();
        output.process();
        //        for (int l = 0 ; l< Buffer::DEFAULT_LENGTH ; l++){
        //            if (sampler->outports().first()->buffer()->data()[l] != 0) {
        //                qDebug() << "k " << k << "not null";
        //            }
        //        }
        QString resul;
        QTextStream flux(&resul);
        qreal value;
        for (int i = 0 ; i < sampler->sampleBuffer()->length() ; i++) {
            if ((value = sampler->sampleBuffer()->data()[i]) != 0) {
            flux <<   value << " ";
        }
        }
        qDebug() << resul;
    }




    // FIXME, Find a better way to "verify" this…
    QVERIFY(res);
}
void TestSampler::setValue(Buffer* buffer, qreal value)
{
    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; i++) {
        buffer->data()[i] = value;
    }
}
