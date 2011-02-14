#ifndef WAVLOOPER_H
#define WAVLOOPER_H

#include "abstraction/module.h"

#include <QObject>

class Buffer;
class OutPort;
class QFile;
class SynthProFactory;

/**
  * Module that loads a WAV file (44100hz, 16bits, mono only)
  * and plays it in loop endlessly.
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
     * Ask for a file name to save to.
     */
    void newFile(const QString&);

    /**
     * Save the first input port buffer into a file.
     */
    void ownProcess();

protected:
    OutPort* m_outPort;

private:
    QString m_fileName;
    QFile* m_inputFile;
    Buffer* m_internalBuffer; // Points on Raw data.
    int m_positionInInternalBuffer;

    bool readWavFile(QFile*);
    int readLittleEndianInt(QFile*);
    int readLittleEndianShort(QFile*);


};

#endif // WAVLOOPER_H
