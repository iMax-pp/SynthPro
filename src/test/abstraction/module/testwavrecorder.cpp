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
    //result = file.seek(SKIP_HEADER_OFFSET);

    // Check the validity of the WAV header.
    // It should be a WAV format. Only 44100hz, 16 bits, mono samples are accepted.

    int sizeData = checkWAVFileHeader(&file);
    result = (sizeData > 0);
    qDebug() << sizeData;



    // FIXME
//    qreal nbCompare = VCO::SIGNAL_INTENSITY / VCO::SIGNAL_INTENSITY * WavRecorder::SIGNAL_OUT_SIGNED_INTENSITY;

//    while (result && !file.atEnd()) {
//        QByteArray data = file.read(2);
//        qreal nb = (int)((data.at(0)) + data.at(1) * 256);
//        //qDebug() << "YOUPIIIIIIIIIII " << nb << " --- " << nbCompare;
//        //result = (nb == qAbs(nbCompare));
//    }

    QVERIFY(result);

    file.close();

    // The WaveGenerator is automatically deleted with the VCO.
    delete mbr;
    delete vco;

}

/// Indicates if the given file has a correct WAV header.
int TestWavRecorder::checkWAVFileHeader(QFile* file)
{
     // Check the WAV format. Only 44100hz, 16 bits, mono samples are accepted.
    if ((QString)(file->read(4)) != "RIFF") {
        return false;
    }

    file->read(4); // Skip Riff size.
    if ((QString)(file->read(8)) != "WAVEfmt ") {
        return false;
    }
    if (readLittleEndianInt(file) != AudioDeviceProvider::BIT_RATE) {
        return false;
    }
    // Compression code.
    if (readLittleEndianShort(file) != 1) {
        return false;
    }
    if (readLittleEndianShort(file) != AudioDeviceProvider::NB_CHANNELS) {
        return false;
    }

    if (readLittleEndianInt(file) != AudioDeviceProvider::OUTPUT_FREQUENCY) {
        return false;
    }

    int blockAlign = AudioDeviceProvider::NB_CHANNELS * (AudioDeviceProvider::BIT_RATE / 8);
    readLittleEndianInt(file);

    if (readLittleEndianShort(file) != blockAlign) {
        return false;
    }
    if (readLittleEndianShort(file) != AudioDeviceProvider::BIT_RATE) {
        return false;
    }

    // Data chunk
    if ((QString)(file->read(4)) != "data") {
        return false;
    }
    int sizeData = readLittleEndianInt(file); // Read data chunk size.

    return sizeData;
}

int TestWavRecorder::readLittleEndianInt(QFile* file)
{
    char tab[4];
    file->read(tab, 4);
    int nb = convertByteToUnsignedByte(tab[3]) * 0x1000000;
    nb += convertByteToUnsignedByte(tab[2]) * 0x10000;
    nb += convertByteToUnsignedByte(tab[1]) * 0x100;
    nb += convertByteToUnsignedByte(tab[0]);

    return nb;
}

int TestWavRecorder::readLittleEndianShort(QFile* file)
{
    char tab[2];
    file->read(tab, 2);
    int nb = tab[1] * 0x100;
    nb += tab[0];

    return nb;
}

int TestWavRecorder::convertByteToUnsignedByte(int nb)
{
    return (nb >= 0 ? nb : 256 + nb);
}
