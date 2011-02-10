#include "testwavegeneratorsaw.h"

#include "abstraction/inport.h"
#include "abstraction/module.h"
#include "abstraction/modulebufferrecorder.h"
#include "abstraction/outport.h"
#include "abstraction/synthpro.h"
#include "abstraction/vco.h"
#include "abstraction/wavegeneratorsaw.h"
#include "factory/simplefactory.h"


#include <QFile>
#include <QtTest/QTest>

void TestWaveGeneratorSaw::testWaveGeneratorSaw()
{
    SynthPro synthPro(0);

    QString fileName = "testWaveGeneratorSaw.wav";

    SimpleFactory factory;
    ModuleBufferRecorder* mbr = factory.createModuleBufferRecorder(0, fileName, NB_ITERATIONS);

    VCO* vco = factory.createVCO(&synthPro);
    vco->setShape("Saw");
    vco->outports().at(0)->connectTo(mbr->inports().at(0));

    for (int i = 0; i < NB_ITERATIONS; i++) {
        vco->process();
        mbr->process();
    }

    QVERIFY(true);
}
