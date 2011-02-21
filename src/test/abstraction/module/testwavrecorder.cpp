#include "testwavrecorder.h"

#include "abstraction/component/inport.h"
#include "abstraction/component/outport.h"
#include "abstraction/module.h"
#include "abstraction/module/vco.h"
#include "abstraction/module/wavrecorder.h"
#include "abstraction/wavegen/wavegeneratorempty.h"
#include "factory/simplefactory.h"

#include <QDebug>
#include <QFile>
#include <QtTest/QTest>

void TestWavRecorder::testWavRecorder()
{
    QString fileName = "testWavRecorder.wav";

    SimpleFactory factory;
    WavRecorder* mbr = factory.createWavRecorder(0, false, NB_ITERATIONS);
    mbr->newFile(fileName);
    mbr->startRecording();
    VCO* vco = factory.createVCO(0);
    vco->setShape("Square");
    vco->outports().first()->connect(mbr->inports().first());

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

    qreal nbCompare = VCO::SIGNAL_INTENSITY / VCO::SIGNAL_INTENSITY * WavRecorder::SIGNAL_OUT_SIGNED_INTENSITY;

    while (result && !file.atEnd()) {
        QByteArray data = file.read(2);
        qreal nb = (int)((data.at(0)) + data.at(1) * 256);
        // qDebug() << "YOUPIIIIIIIIIII " << nb << " --- " << nbCompare;
        result = (nb == qAbs(nbCompare));
    }

    QVERIFY(result);

    file.close();

    // The WaveGenerator is automatically deleted with the VCO.
    delete mbr;
    delete vco;

}
