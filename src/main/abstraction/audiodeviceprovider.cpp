#include "audiodeviceprovider.h"

#include <QAudioDeviceInfo>
#include <QAudioOutput>

#include <QDebug>

AudioDeviceProvider::AudioDeviceProvider()
    : m_initialized(false)
    , m_deviceUsed(false)
    , m_device(0)
    , m_audioOutput(0)
{
    initializeAudioOutput();
}

AudioDeviceProvider::AudioDeviceProvider(AudioDeviceProvider&)
    : m_initialized(false)
    , m_deviceUsed(false)
    , m_device(0)
    , m_audioOutput(0)
{
    initializeAudioOutput();
}

AudioDeviceProvider::~AudioDeviceProvider()
{
    releaseDevice();
    stop();
    if (m_audioOutput) {
        delete m_audioOutput;
    }
}

AudioDeviceProvider& AudioDeviceProvider::instance()
{
    static AudioDeviceProvider instance;
    return instance;
}

bool AudioDeviceProvider::initializeAudioOutput()
{
    if (m_initialized) {
        return true;
    }

    // Create the desired output format.
#if QT_VERSION < 0x40700
    m_audioFormat.setFrequency(OUTPUT_FREQUENCY);
    m_audioFormat.setChannels(NB_CHANNELS);
#else
    m_audioFormat.setSampleRate(OUTPUT_FREQUENCY);
    m_audioFormat.setChannelCount(NB_CHANNELS);
#endif

    m_audioFormat.setSampleSize(BIT_RATE);
    m_audioFormat.setSampleType(QAudioFormat::SignedInt);
    m_audioFormat.setByteOrder(QAudioFormat::LittleEndian);
    m_audioFormat.setCodec("audio/pcm");

    // Check if the default output device accepts the format. If yes, no need to search any further.
    QAudioDeviceInfo audioDevice(QAudioDeviceInfo::defaultOutputDevice());
    bool result = audioDevice.isFormatSupported(m_audioFormat);

    if (!result) {
        qWarning() << "Default output device unable to support requested audio format.";
        // Search for other devices that support the format.
        QList<QAudioDeviceInfo> outputDevices = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);

        // Search for the first output that satisfies the requested output format.
        int i = 0, size = outputDevices.count();

        while (!result && i < size) {
            audioDevice = outputDevices.at(i);

            if (audioDevice.isFormatSupported(m_audioFormat)) {
                result = true;
            } else {
                i++;
            }
        }
    }

    // Instanciate the audio output and set its buffer size.
    if (result) {
        m_audioOutput = new QAudioOutput(audioDevice, m_audioFormat);
        m_audioOutput->setBufferSize(BUFFER_SIZE);
        m_initialized = true;
    }

    return result;
}

QIODevice* AudioDeviceProvider::device()
{
    if (!m_initialized && !initializeAudioOutput()) {
        // If the device can't be initialized, return 0.
        return 0;
    }

    // Release a device, if it hasn't been given before.
    if (!m_deviceUsed && m_audioOutput) {
        m_device = m_audioOutput->start();
        m_deviceUsed = true;
        m_device->open(QIODevice::WriteOnly);

        return m_device;
    }

    return 0;
}

void AudioDeviceProvider::releaseDevice()
{
    if (m_deviceUsed) {
        m_device->close();
        m_deviceUsed = false;
    }
}

void AudioDeviceProvider::stop()
{
    if (m_audioOutput) {
        m_audioOutput->stop();
    }
}

QAudioFormat* AudioDeviceProvider::audioFormat()
{
    return &m_audioFormat;
}

QAudioOutput* AudioDeviceProvider::audioOutput()
{
    return m_audioOutput;
}
