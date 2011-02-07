#include "testwavegeneratorsaw.h"

#include "src/main/abstraction/module.h"
#include "src/main/abstraction/modulebufferrecorder.h"
#include "src/main/abstraction/vco.h"
#include "src/main/abstraction/wavegeneratorsaw.h"
#include "src/main/factory/simplefactory.h"

#include <QFile>
#include <QtTest/QTest>

void TestWaveGeneratorSaw::testWaveGeneratorSaw()
{
    QString fileName = "testWaveGeneratorSaw.wav";

    SimpleFactory factory;
    ModuleBufferRecorder* mbr = factory.createModuleBufferRecorder(0, fileName, NB_ITERATIONS);

    WaveGeneratorSaw* waveGeneratorSaw = new WaveGeneratorSaw();

    VCO* vco = factory.createVCO();
    vco->setWaveGenerator(waveGeneratorSaw);
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
