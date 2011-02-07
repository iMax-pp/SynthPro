#include "testwavegeneratorsinus.h"

#include "src/main/abstraction/inport.h"
#include "src/main/abstraction/module.h"
#include "src/main/abstraction/modulebufferrecorder.h"
#include "src/main/abstraction/vco.h"
#include "src/main/abstraction/wavegeneratorsinus.h"
#include "src/main/factory/simplefactory.h"

#include <QFile>
#include <QtTest/QTest>

void TestWaveGeneratorSinus::testWaveGeneratorSinus()
{
    QString fileName = "testWaveGeneratorSinus.wav";

    SimpleFactory factory;
    ModuleBufferRecorder* mbr = factory.createModuleBufferRecorder(0, fileName, NB_ITERATIONS);

    WaveGeneratorSinus* waveGeneratorSinus = new WaveGeneratorSinus();

    VCO* vco = factory.createVCO();
    vco->setWaveGenerator(waveGeneratorSinus);
    vco->outports().at(0)->connectTo(mbr->inports().at(0));

    for (int i = 0; i < NB_ITERATIONS; i++) {
        vco->process();
        mbr->process();
    }

    QVERIFY(true);

    // The WaveGenerator is automatically deleted with the VCO.
    delete mbr;
    delete vco;

}
