#include "wavlooper.h"

#include "abstraction/audiodeviceprovider.h"
#include "abstraction/component/dimmer.h"
#include "abstraction/component/outport.h"
#include "abstraction/module/vco.h"
#include "abstraction/synthpro.h"
#include "factory/synthprofactory.h"

#include <QDebug>
#include <QFile>

WavLooper::WavLooper(SynthPro* parent)
    : Module(parent)
    , m_outPort(0)
    , m_sDimmer(0)
    , m_fileName("input.wav")
    , m_inputFile(0)
    , m_internalBuffer(0)
    , m_positionInInternalBuffer(0)
    , m_speed(0)
{
}

WavLooper::~WavLooper()
{
    if (m_inputFile) {
        m_inputFile->close();
    }

    if (m_internalBuffer) {
        delete[] m_internalBuffer->data();
    }
}

void WavLooper::initialize(SynthProFactory* factory)
{
    m_outPort = factory->createOutPortReplicable(this, "out");
    m_outports.append(m_outPort);

    m_sDimmer = factory->createDialDimmer("Speed", S_MIN, S_MAX, S_DEFAULT, this);
}

void WavLooper::newFile(const QString& filename)
{
    if (m_inputFile) {
        m_inputFile->close();
    }

    // Open a new file.
    m_fileName = filename;
    m_inputFile = new QFile(filename);

    if (!m_inputFile->open(QIODevice::ReadOnly)) {
        qWarning() << "Unable to open file. " << m_inputFile->fileName();
    } else if (!readWavFile(m_inputFile)) {
        qWarning("Format of file read unknown.");
    }

    m_inputFile->close();
}

void WavLooper::ownProcess()
{
    m_speed = m_sDimmer->value();

    if (m_internalBuffer) {
        qreal* dataInPort = m_internalBuffer->data();
        qreal* dataOutPort = m_outPort->buffer()->data();
        qreal sizeInternalBuffer = m_internalBuffer->length();

        for (int i = 0; i < Buffer::DEFAULT_LENGTH; i++) {
            dataOutPort[i] = dataInPort[(int)m_positionInInternalBuffer];
            m_positionInInternalBuffer += m_speed;
            if (m_positionInInternalBuffer >= sizeInternalBuffer) {
                m_positionInInternalBuffer = 0;
            }
        }
    }
}

bool WavLooper::readWavFile(QFile* file)
{
     // Check the WAV format.
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
    if (readLittleEndianShort(file) != 1) {
        return false;
    } // Compression code.
    if (readLittleEndianShort(file) != AudioDeviceProvider::NB_CHANNELS) {
        return false;
    }

    // FIXME
    // if (readLittleEndianInt(file) != AudioDeviceProvider::OUTPUT_FREQUENCY) { return false; }
    readLittleEndianInt(file);

    // FIXME too !!
    int blockAlign = AudioDeviceProvider::NB_CHANNELS * (AudioDeviceProvider::BIT_RATE / 8);
    readLittleEndianInt(file);
    // qDebug() << nb;
    // if (nb != (blockAlign * AudioDeviceProvider::OUTPUT_FREQUENCY)) { return false; }

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
    file->read(4); // Skip data chunk size.

    // Copy the wave into the buffer.
    int wavSize = (file->size() - file->pos()); // / 2; // /2 because we stock only qreal, but read double char.
    if (m_internalBuffer) {
        delete[] m_internalBuffer;
    }
    m_internalBuffer = new Buffer(wavSize);

    for (int i = 0; i < wavSize; i += 2) {
        // Convert the 16 bits little endian signal into an amplitude.
        m_internalBuffer->data()[i] = readLittleEndianShort(file) / (65536 / 2 / VCO::SIGNAL_INTENSITY);
        m_internalBuffer->data()[i + 1] = m_internalBuffer->data()[i];
    }

    return true;
}

int WavLooper::readLittleEndianInt(QFile* file)
{
    char tab[4];
    file->read(tab, 4);
    int nb = tab[3] * 0x1000000;
    nb += tab[2] * 0x10000;
    nb += tab[1] * 0x100;
    nb += tab[0];
    return nb;
}

int WavLooper::readLittleEndianShort(QFile* file)
{
    char tab[2];
    file->read(tab, 2);
    int nb = tab[1] * 0x100;
    nb += tab[0];
    return nb;
}
