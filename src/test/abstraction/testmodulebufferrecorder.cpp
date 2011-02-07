#include "testmodulebufferrecorder.h"

#include "src/main/abstraction/inport.h"
#include "src/main/abstraction/module.h"
#include "src/main/abstraction/modulebufferrecorder.h"
#include "src/main/abstraction/vco.h"
#include "src/main/abstraction/wavegeneratorempty.h"
#include "src/main/factory/simplefactory.h"

#include <QDebug>
#include <QFile>
#include <QtTest/QTest>

void TestModuleBufferRecorder::testModuleBufferRecorder()
{
    QString fileName = "testModuleBufferRecorder.wav";

    SimpleFactory factory;
    ModuleBufferRecorder* mbr = factory.createModuleBufferRecorder(0, fileName, NB_ITERATIONS);

    WaveGeneratorEmpty* waveGeneratorDummy = new WaveGeneratorEmpty();

    VCO* vco = factory.createVCO();
    vco->setWaveGenerator(waveGeneratorDummy);
    vco->outports().at(0)->connectTo(mbr->inports().at(0));

    for (int i = 0; i < NB_ITERATIONS; i++) {
        vco->process();
        mbr->process();
    }

    // Now the sound is generated, we load the file, skip the WAV header, and we should
    // find only 0 till the end of the file.
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Unable to load output file.");
        QVERIFY(false);
        return;
    }

    bool result;
    result = file.seek(SKIP_HEADER_OFFSET);

    while (result && !file.atEnd()) {
       QByteArray data = file.read(1);
       result = (data.at(0) == 0);
    }

    QVERIFY(result);

    file.close();

    // The WaveGenerator is automatically deleted with the VCO.
    delete mbr;
    delete vco;

}
