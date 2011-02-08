#include "testwavegeneratorsquare.h"

#include "abstraction/dimmer.h"
#include "abstraction/module.h"
#include "abstraction/modulebufferrecorder.h"
#include "abstraction/vco.h"
#include "abstraction/wavegeneratorsquare.h"
#include "factory/simplefactory.h"

#include <QFile>
#include <QtTest/QTest>

void TestWaveGeneratorSquare::testWaveGeneratorSquare()
{
    QString fileName = "testWaveGeneratorSquare.wav";

    SimpleFactory factory;
    ModuleBufferRecorder* mbr = factory.createModuleBufferRecorder(0, fileName, NB_ITERATIONS);

    WaveGeneratorSquare* waveGeneratorSquare = new WaveGeneratorSquare();

    VCO* vco = factory.createVCO();
    vco->setWaveGenerator(waveGeneratorSquare);
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
