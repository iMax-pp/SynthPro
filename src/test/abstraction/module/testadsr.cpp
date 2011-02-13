#include "testadsr.h"

#include "abstraction/buffer.h"
#include "abstraction/component/inport.h"
#include "abstraction/component/outport.h"
#include "abstraction/mock/mockserializerwell.h"
#include "abstraction/synthpro.h"
#include "factory/simplefactory.h"

#include <QDebug>
#include <QTextStream>

// #include <iostream>

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
    adsr->ownProcess();


    QVERIFY(true);

    delete synth;
}
void TestADSR::testADSR2Buffers()
{
    // FILE *outfile = fopen("adsr","w");

    QString result;
    QTextStream stream(&result);
    // QTextStream stream(outfile);

    SimpleFactory factory;
    SynthPro* synth = factory.createSynthPro();
    ADSR* adsr = factory.createADSR(synth);

    adsr->setAttackValue(0.005);
    adsr->setDecayValue(0.008);
    adsr->setSustainValue(0.71);
    adsr->setReleaseValue(0.008);

    Buffer* inBuffer = adsr->inports().first()->buffer();

    qDebug() << "start";

    for (int i = 0 ; i< inBuffer->length() / 2 ; i++) {
        inBuffer->data()[i] = 0;
    }
    for (int i= inBuffer->length() / 2 ; i< inBuffer->length() ; i++) {
        inBuffer->data()[i] = 1;
    }

        /*adsr->ownProcess();
    for (int i = 0 ; i< inBuffer->length() ; i++) {
        stream  << i << " " << adsr->outports().first()->buffer()->data()[i] << "\n";

    }*/



    for (int i = 0 ; i< inBuffer->length() / 4 ; i++) {
        inBuffer->data()[i] = 1;
    }
    for (int i= inBuffer->length() / 4 ; i< inBuffer->length() ; i++) {
        inBuffer->data()[i] = 0;
    }
    adsr->ownProcess();

    /*for (int i = 0 ; i< inBuffer->length() ; i++) {
        int index = i+900;
        stream  << index << " " <<  adsr->outports().first()->buffer()->data()[i] << "\n";

    }*/

    // qDebug() << result;
    QVERIFY(true);
    // fclose(outfile);
    delete synth;
}
