#ifndef WAVRECORDER_H
#define WAVRECORDER_H

#include "abstraction/module.h"

class InPort;
class PushButton;
class QFile;
class SynthProFactory;

/**
 * Module that saves into a WAV file what is sent in its input port.
 * If the port is disconnected, pause the recording till it is connected again.
 * Close the file automatically after a fixed number of processing (if this feature is used),
 * or if stopRecording() is called.
 */
class WavRecorder : public virtual Module {
    Q_OBJECT

public:
    static const int SIGNAL_OUT_SIGNED_INTENSITY = 32767;

    WavRecorder(SynthPro*, int nbProcessingBeforeSaving = 10);
    virtual ~WavRecorder();

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

public slots:
    /**
     * Start the recording into the current file.
     */
    void startRecording();

    /**
     * Stop the recording into the current file.
     * @warning It doesn't close the file, just pause the recording.
     */
    void stopRecording();

protected:
    InPort* m_inPort;
    PushButton* m_recordButton;
    PushButton* m_stopButton;

    /**
     * Write the right size of the chunks and data,
     * which position has been saved while writing the buffer(s).
     * Then close the file.
     */
    void closeWAVFile();

private:
    QString m_fileName;
    QFile* m_outputFile;
    bool m_isRecording;
    const int m_nbProcessingBeforeSaving;
    int m_nbProcessingSaved;

    int m_riffDataSizePosition;
    int m_waveDataSizePosition;
    int m_dataLength;
    char* m_bufferForNumbers; // Little buffer used to write numbers to the file. NOT thread safe.

    /**
     * Create the WAV header of the output file, as well as setting up
     * the dynamic size pointers.
     */
    void createWAVHeader(QFile*);

    /**
     * Helper method. Add a little endian int32 to a given file.
     */
    void addLittleEndianIntToFile(QFile*, int nb);

    /**
     * Helper method. Add a little endian short (16 bits) to a given file.
     */
    void addLittleEndianShortToFile(QFile*, int nb);
};

#endif // WAVRECORDER_H
