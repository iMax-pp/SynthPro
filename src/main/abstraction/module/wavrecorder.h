#ifndef WAVRECORDER_H
#define WAVRECORDER_H

#include "abstraction/module.h"

class InPort;
class QFile;
class SynthProFactory;

/**
  * Module that saves into a WAV file what is sent in his input port.
  * If more than one in port are given, take the first one only.
  * If the first port is disconnected, pause the recording till it is connected again.
  * Close the file automatically after a fixed number of processing.
  */
class WavRecorder : public virtual Module {

public:
    WavRecorder(SynthPro*, QString fileName = "output.wav", int nbProcessingBeforeSaving = 5);
    virtual ~WavRecorder();

    /**
      * Required method in order to instanciate the ports. Used by the factory.
      */
    void initialize(SynthProFactory*);

    /**
     * Save the first input port buffer into a file.
     */
    void ownProcess();

protected:
    InPort* m_inPort;

private:
    static const int SIGNAL_OUT_SIGNED_INTENSITY = 32767;

    QString m_fileName;
    const int m_nbProcessingBeforeSaving;
    int m_nbProcessingSaved;
    QFile* m_outputFile;

    int m_riffDataSizePosition;
    int m_waveDataSizePosition;
    int m_dataLength;
    char* m_bufferForNumbers; // Little buffer used to write numbers to the file. NOT thread safe.

    /**
      * Creates the WAV header of the output file, as well as setting up
      * the dynamic size pointers.
      */
    void createWAVHeader(QFile*);

    /**
      * Write the right size of the chunks and data,
      * which position has been saved while writing the buffer(s).
      * Then close the file.
      */
    void closeWAVFile(QFile*);

    /**
      * Helper method. Adds a little endian int32 to a given file.
      */
    void addLittleEndianIntToFile(QFile*, int nb);

    /**
      * Helper method. Adds a little endian short (16 bits) to a given file.
      */
    void addLittleEndianShortToFile(QFile*, int nb);
};

#endif // WAVRECORDER_H
