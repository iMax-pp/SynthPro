#include "testwavegeneratorsinus.h"

#include "abstraction/inport.h"
#include "abstraction/module.h"
#include "abstraction/outport.h"
#include "abstraction/synthpro.h"
#include "abstraction/vco.h"
#include "abstraction/wavegeneratorsinus.h"
#include "abstraction/wavrecorder.h"
#include "factory/simplefactory.h"

#include <QFile>
#include <QtTest/QTest>

void TestWaveGeneratorSinus::testWaveGeneratorSinus()
{
    SynthPro synthPro(0);

    QString fileName = "testWaveGeneratorSinus.wav";

    SimpleFactory factory;
    WavRecorder* mbr = factory.createModuleBufferRecorder(0, fileName, NB_ITERATIONS);

    VCO* vco = factory.createVCO(&synthPro);
    vco->setShape("Sinus");
    vco->outports().at(0)->connectTo(mbr->inports().at(0));

    for (int i = 0; i < NB_ITERATIONS; i++) {
        vco->process();
        mbr->process();
    }

    QVERIFY(true);
}
