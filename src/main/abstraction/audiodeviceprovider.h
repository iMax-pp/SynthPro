#ifndef AUDIODEVICEPROVIDER_H
#define AUDIODEVICEPROVIDER_H

#include <QAudioFormat>

class QAudioOutput;
class QIODevice;

/**
  * Provides a device, linked to an audio output, in which
  * can be sent data to be played by the output, in a
  * Push mode.
  *
  * For this project, we only consider one audio format, and
  * only support the one we use.
  */
class AudioDeviceProvider
{
public:
    AudioDeviceProvider();
    ~AudioDeviceProvider();

    /**
      * Finds an audio output, indicate if a valid one has been
      * found, initialize it if yes.
      */
    bool initializeAudioOutput();

    /**
      * Start the returned device through the audio output in Push
      * mode. Must be called after the initializeAudioOutput()
      * method, else it returns 0.
      */
    QIODevice* start();

    /**
      * Stop the audio output.
      */
    void stop();

    /**
      * Return the audio format.
      */
    QAudioFormat* audioFormat();

    /**
      * Return the audio output.
      */
    QAudioOutput* audioOutput();

private:
    static const int OUTPUT_FREQUENCY = 44100;
    static const int BIT_RATE = 16;
    static const int NB_CHANNELS = 1; // We create Mono sounds only.
    static const int BUFFER_SIZE = 5000;

    QAudioFormat m_audioFormat; // Format used by the audio output.
    QAudioOutput* m_audioOutput;
};

#endif // AUDIODEVICEPROVIDER_H
