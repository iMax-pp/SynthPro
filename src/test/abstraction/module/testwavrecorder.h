#ifndef TESTWAVRECORDER_H
#define TESTWAVRECORDER_H

class QFile;

#include <QObject>

/**
  * The test consists in linking a VCO with a WaveGeneratorSquare,
  * to the ModuleBufferRecorder. We then reload the file, check the WAV header, and
  * make sure the whole file has either high and low shelf..
  */
class TestWavRecorder : public QObject {
    Q_OBJECT

private:
    /**
     * Read the given file (must be already open), and check if the format is correct.
     * @returns the size of the actual data to read, or -1 if an error occured.
     */
    int checkWAVFileHeader(QFile*);

    /**
     * Read an int (32 bits) encoded in little endian from the given file.
     */
    int readLittleEndianInt(QFile*);

    /**
     * Read an short (16 bits) encoded in little endian from the given file.
     */
    int readLittleEndianShort(QFile*);

    /**
     * Convert a signed byte (8 bits) to an unsigned byte.
     */
    int convertByteToUnsignedByte(int);

private slots:
    void testWavRecorder();

private:
    static const int NB_ITERATIONS = 50;
    static const int SKIP_HEADER_OFFSET = 64; // Not accurate, but no needs to be.
};

#endif // TESTWAVRECORDER_H
