#include "testmodulebufferrecorder.h"

#include "abstraction/component/inport.h"
#include "abstraction/component/outport.h"
#include "abstraction/component/port.h"
#include "abstraction/module.h"
#include "abstraction/module/vco.h"
#include "abstraction/module/wavrecorder.h"
#include "abstraction/wavegen/wavegeneratorempty.h"
#include "factory/simplefactory.h"

#include <QDebug>
#include <QFile>
#include <QtTest/QTest>

void TestModuleBufferRecorder::testModuleBufferRecorder()
{
    QString fileName = "testModuleBufferRecorder.wav";

    SimpleFactory factory;
    WavRecorder* mbr = factory.createWavRecorder(0, NB_ITERATIONS);
    mbr->newFile(fileName);
    mbr->startRecording();

    VCO* vco = factory.createVCO(0);
    vco->setShape("Empty");
    vco->outports().first()->connections().first()->connect(mbr->inports().first()->connections().first());

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
