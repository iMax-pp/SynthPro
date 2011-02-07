#include "testmodulebufferrecorder.h"

#include "src/main/abstraction/modulebufferrecorder.h"
#include "src/main/abstraction/inport.h"
#include "src/main/abstraction/module.h"
#include "src/main/factory/simplefactory.h"
#include "src/main/abstraction/vco.h"
#include "src/main/abstraction/wavegeneratordummy.h"

#include <QtTest/QTest>

void TestModuleBufferRecorder::testModuleBufferRecorder()
{
    SimpleFactory factory;
    ModuleBufferRecorder* mbr = factory.createModuleBufferRecorder(0, "output.wav", NB_ITERATIONS);

    WaveGeneratorDummy* waveGeneratorDummy = new WaveGeneratorDummy();

    VCO* vco = factory.createVCO();
    vco->setWaveGenerator(waveGeneratorDummy);
    vco->outports().at(0)->connectTo(mbr->inports().at(0));

    for (int i = 0; i < NB_ITERATIONS; i++) {
        mbr->process();
    }

    QVERIFY(true);

    // The WaveGenerator is automatically deleted with the VCO.
    delete mbr;
    delete vco;

}
