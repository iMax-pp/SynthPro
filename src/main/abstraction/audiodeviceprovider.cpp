#include "audiodeviceprovider.h"

#include <QAudioDeviceInfo>
#include <QAudioOutput>

#include <QDebug>

AudioDeviceProvider::AudioDeviceProvider()
    : m_audioOutput(0)
{
}

AudioDeviceProvider::~AudioDeviceProvider()
{
    stop();

    if (m_audioOutput) {
        delete m_audioOutput;
    }
}

bool AudioDeviceProvider::initializeAudioOutput()
{
    // Stop the audio output in case it had been started before.
    stop();

    // Create the desired output format.
    m_audioFormat.setFrequency(OUTPUT_FREQUENCY); // Should use SetSampleRate, but QT4.5 doesn't support it.
    m_audioFormat.setChannels(NB_CHANNELS); // Should use SetChannelCount, but QT4.5 doesn't support it.
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
    }

    return result;
}

QIODevice* AudioDeviceProvider::start()
{
    return m_audioOutput ? m_audioOutput->start() : 0;
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
