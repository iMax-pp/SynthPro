#include "testwavegeneratortriangle.h"

#include "abstraction/component/inport.h"
#include "abstraction/component/outport.h"
#include "abstraction/component/port.h"
#include "abstraction/module.h"
#include "abstraction/module/vco.h"
#include "abstraction/module/wavrecorder.h"
#include "abstraction/synthpro.h"
#include "abstraction/wavegen/wavegeneratortriangle.h"
#include "factory/simplefactory.h"

#include <QFile>
#include <QtTest/QTest>

void TestWaveGeneratorTriangle::testWaveGeneratorTriangle()
{
    SynthPro synthPro(0);

    QString fileName = "testWaveGeneratorTriangle.wav";

    SimpleFactory factory;
    WavRecorder* mbr = factory.createWavRecorder(0, NB_ITERATIONS);
    mbr->newFile(fileName);
    mbr->startRecording();
    VCO* vco = factory.createVCO(&synthPro);
    vco->setShape("Triangle");
    vco->outports().first()->connections().first()->connect(mbr->inports().first()->connections().first());

    for (int i = 0; i < NB_ITERATIONS; i++) {
        vco->process();
        mbr->process();
    }

    QVERIFY(true);
}
