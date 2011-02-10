#include "testmodulebufferrecorder.h"

#include "abstraction/inport.h"
#include "abstraction/module.h"
#include "abstraction/modulebufferrecorder.h"
#include "abstraction/outport.h"
#include "abstraction/vco.h"
#include "abstraction/wavegeneratorempty.h"
#include "factory/simplefactory.h"

#include <QDebug>
#include <QFile>
#include <QtTest/QTest>

void TestModuleBufferRecorder::testModuleBufferRecorder()
{
    QString fileName = "testModuleBufferRecorder.wav";

    SimpleFactory factory;
    ModuleBufferRecorder* mbr = factory.createModuleBufferRecorder(0, fileName, NB_ITERATIONS);

    VCO* vco = factory.createVCO(0);
    vco->setShape("Empty");
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
