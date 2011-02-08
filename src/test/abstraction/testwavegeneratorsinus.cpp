#include "testwavegeneratorsinus.h"

#include "abstraction/module.h"
#include "abstraction/modulebufferrecorder.h"
#include "abstraction/vco.h"
#include "abstraction/wavegeneratorsinus.h"
#include "factory/simplefactory.h"

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
