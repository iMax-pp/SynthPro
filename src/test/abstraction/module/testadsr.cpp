#include "testadsr.h"

#include "abstraction/audiodeviceprovider.h"
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
    Buffer* output = new Buffer(3*Buffer::DEFAULT_LENGTH);

    qreal fixedAttack = 0.005;
    qreal fixedDecay = 0.005;
    qreal fixedSustain = 0.71;
    qreal fixedRealease = 0.005;

    adsr->setAttackValue(fixedAttack);
    adsr->setDecayValue(fixedDecay);
    adsr->setSustainValue(fixedSustain);
    adsr->setReleaseValue(fixedRealease);

    Buffer* inBuffer = adsr->inports().first()->buffer();

    for (int i = 0 ; i< inBuffer->length() / 2 ; i++) {
        inBuffer->data()[i] = 0;
    }
    for (int i= inBuffer->length() / 2 ; i< inBuffer->length() ; i++) {
        inBuffer->data()[i] = 1;
    }

    adsr->ownProcess();
    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; i++) {
        output->data()[i] = adsr->outports().first()->buffer()->data()[i];
    }


    for (int i = 0 ; i< inBuffer->length(); i++) {
        inBuffer->data()[i] = 1;
    }

    adsr->ownProcess();
    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; i++) {
        output->data()[i + Buffer::DEFAULT_LENGTH] = adsr->outports().first()->buffer()->data()[i];
    }

    for (int i = 0 ; i< inBuffer->length(); i++) {
        inBuffer->data()[i] = 0;
    }
    adsr->ownProcess();
    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; i++) {
        output->data()[i + 2*Buffer::DEFAULT_LENGTH] = adsr->outports().first()->buffer()->data()[i];
    }


    qreal oldValue = output->data()[0];
    int i = 1;
    while (oldValue == 0) {
        oldValue = output->data()[i];
        i++;
    }
    int wait = i;
    while (oldValue < output->data()[i]) {
        oldValue = output->data()[i];
        i++;
    }
    int attack = i;
    while (oldValue > output->data()[i]) {
        oldValue = output->data()[i];
        i++;
    }
    int decay = i;

    while (oldValue == output->data()[i]) {
        oldValue = output->data()[i];
        i++;
    }
    qreal sustain = oldValue;
    int beginRealease = i;
    while (oldValue > output->data()[i]) {
        oldValue = output->data()[i];
        i++;
    }
    int release = i - beginRealease;
    decay = decay - attack;
    attack = attack - wait;
    // after processing in three buffers and analysis  of the output, we verify the values of a, d, s & r are ok
    QVERIFY(qAbs(attack - fixedAttack * AudioDeviceProvider::OUTPUT_FREQUENCY) < 2);
    QVERIFY(qAbs(decay - fixedDecay * AudioDeviceProvider::OUTPUT_FREQUENCY) < 2);
    QVERIFY(qAbs(sustain - fixedSustain) < 0.01);
    QVERIFY(qAbs(release - fixedRealease* AudioDeviceProvider::OUTPUT_FREQUENCY) < 2);
    delete synth;
}
