#include "testwavegeneratorsquare.h"

#include "abstraction/dimmer.h"
#include "abstraction/inport.h"
#include "abstraction/module.h"
#include "abstraction/outport.h"
#include "abstraction/port.h"
#include "abstraction/synthpro.h"
#include "abstraction/vco.h"
#include "abstraction/wavegeneratorsquare.h"
#include "abstraction/wavrecorder.h"
#include "factory/simplefactory.h"

#include <QFile>
#include <QtTest/QTest>

void TestWaveGeneratorSquare::testWaveGeneratorSquare()
{
    SynthPro synthPro(0);

    QString fileName = "testWaveGeneratorSquare.wav";

    SimpleFactory factory;
    WavRecorder* mbr = factory.createModuleBufferRecorder(0, fileName, NB_ITERATIONS);

    VCO* vco = factory.createVCO(&synthPro);
    vco->setShape("Square");
    vco->outports().first()->connections().first()->connect(mbr->inports().first()->connections().first());

    for (int i = 0; i < NB_ITERATIONS; i++) {
        vco->process();
        mbr->process();
    }

    QVERIFY(true);
}
