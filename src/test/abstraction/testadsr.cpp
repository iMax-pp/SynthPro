#include "testadsr.h"

#include "abstraction/buffer.h"
#include "abstraction/inport.h"
#include "abstraction/mockserializerwell.h"
#include "abstraction/outport.h"
#include "abstraction/synthpro.h"
#include "factory/simplefactory.h"

#include <QDebug>
#include <QTextStream>
void TestADSR::testADSR()
{
    SimpleFactory factory;
    SynthPro* synth = factory.createSynthPro();
    ADSR* adsr = factory.createADSR(synth);

    adsr->setAttackValue(0.001);
    adsr->setDecayValue(0.001);
    adsr->setSustainValue(0.1);
    adsr->setReleaseValue(0.002);

    Buffer* inBuffer = adsr->inports().first()->buffer();

    for (int i = 0 ; i< inBuffer->length() / 20 ; i++) {
        inBuffer->data()[i] = 0;
    }
    for (int i= inBuffer->length() / 20 ; i< inBuffer->length()*4 / 5 ; i++) {
        inBuffer->data()[i] = 1;
    }
    for (int i= inBuffer->length()*4 / 5 ; i< inBuffer->length() ; i++) {
        inBuffer->data()[i] = 0;
    }
    //   adsr->ownProcess();
    adsr->ownProcess();


    QVERIFY(true);
}
void TestADSR::testADSR2Buffers()
{
    QString result;
    QTextStream stream(&result);

    SimpleFactory factory;
    SynthPro* synth = factory.createSynthPro();
    ADSR* adsr = factory.createADSR(synth);

    adsr->setAttackValue(0.015);
    adsr->setDecayValue(0.008);
    adsr->setSustainValue(0.71);
    adsr->setReleaseValue(0.013);

    Buffer* inBuffer = adsr->inports().first()->buffer();

    qDebug() << "start";

    for (int i = 0 ; i< inBuffer->length() / 2 ; i++) {
        inBuffer->data()[i] = 0;
    }
    for (int i= inBuffer->length() / 2 ; i< inBuffer->length()*4 / 5 ; i++) {
        inBuffer->data()[i] = 1;
    }
    for (int i= inBuffer->length()*4 / 5 ; i< inBuffer->length() ; i++) {
        inBuffer->data()[i] = 1;
    }
    adsr->ownProcess();

    // affichage
    for (int i= 0 ; i< inBuffer->length() ; i++) {
        stream  << adsr->outports().first()->buffer()->data()[i]  << " " << inBuffer->data()[i] <<"\n";
    }



    for (int i = 0 ; i< inBuffer->length() / 4 ; i++) {
        inBuffer->data()[i] = 1;
    }
    for (int i= inBuffer->length() / 4 ; i< inBuffer->length()*4 / 5 ; i++) {
        inBuffer->data()[i] = 0;
    }
    for (int i= inBuffer->length()*4 / 5 ; i< inBuffer->length() ; i++) {
        inBuffer->data()[i] = 0;
    }
    adsr->ownProcess();
    // affichage
    stream << "buffer 2";
    for (int i= 0 ; i< inBuffer->length() ; i++) {
        stream  << adsr->outports().first()->buffer()->data()[i] << " " << inBuffer->data()[i] << "\n";
    }
    qDebug() << result;
    QVERIFY(true);
}
