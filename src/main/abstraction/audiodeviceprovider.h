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
  * Only one device can be given at the same time. If a second
  * request is made for the device, it receives a 0.
  * Once a device is not used anymore, the user should release
  * it.
  *
  * For this project, we only consider one audio format, and
  * only support the one we use.
  */
class AudioDeviceProvider {

public:
    ~AudioDeviceProvider();

    static AudioDeviceProvider& instance();

    /**
      * Finds an audio output, indicate if a valid one has been
      * found, initialize it if yes.
      */
    bool initializeAudioOutput();

    /**
      * Return the device through the audio output in Push
      * mode. If initializeAudioOutput() wasn't called, it does it.
      * If the device has already been given, 0 is also returned.
      */
    QIODevice* device();

    /**
      * Release the device, so that it can be used again by another entity.
      */
    void releaseDevice();

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

    static const int OUTPUT_FREQUENCY = 44100;
    static const int BIT_RATE = 16;
    static const int NB_CHANNELS = 1; // We create Mono sounds only.
    static const int BUFFER_SIZE = 5000;

private:
    AudioDeviceProvider();

    bool m_initialized;
    bool m_deviceUsed;
    QIODevice* m_device;
    QAudioFormat m_audioFormat; // Format used by the audio output.
    QAudioOutput* m_audioOutput;
};

#endif // AUDIODEVICEPROVIDER_H
