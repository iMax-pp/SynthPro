#ifndef WAVLOOPER_H
#define WAVLOOPER_H

#include "abstraction/module.h"

#include <QObject>

class Buffer;
class Dimmer;
class OutPort;
class QFile;
class SynthProFactory;

/**
 * Module that loads a WAV file (44100hz, 16bits, mono only)
 * and plays it endlessly in loop.
 */
class WavLooper : public virtual Module {
    Q_OBJECT

public:
    explicit WavLooper(SynthPro*);
    virtual ~WavLooper();

    /**
     * Required method in order to instanciate the ports. Used by the factory.
     */
    void initialize(SynthProFactory*);

    /**
     * Ask for a file name to load.
     */
    bool newFile(const QString&);

    /**
     * Save the first input port buffer into a file.
     */
    void ownProcess();

    static const qreal S_MIN = 0.4;
    static const qreal S_MAX = 2;
    static const qreal S_DEFAULT = 1;

protected:
    OutPort* m_outPort;
    Dimmer* m_sDimmer;

private:
    QString m_fileName;
    QFile* m_inputFile;
    Buffer* m_internalBuffer; // Points on Raw data.
    qreal m_positionInInternalBuffer;
    qreal m_speed;

    /**
     * Read the given file (must be already open), check if the format is correct, and fill the
     * internal Buffer with the WAV data.
     */
    bool readWavFile(QFile*);
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


};

#endif // WAVLOOPER_H
