#include "moduleout.h"

#include "audiodeviceprovider.h"
#include "buffer.h"
#include "clock.h"
#include "factory/synthprofactory.h"
#include "inport.h"
#include "sequencer.h"

#include <QAudioOutput>
#include <QDebug>

ModuleOut::ModuleOut(QIODevice* device, QAudioOutput* audioOutput, QObject* parent)
    : Module(parent)
    , m_device(device)
    , m_audioOutput(audioOutput)
    , m_generationBuffer(0)
    , m_generationBufferIndex(0)
    , m_nbGeneratedBytesRemaining(0)
    , m_sequencer(Sequencer::instance())
    // , m_manageSound(false)
{
}

ModuleOut::~ModuleOut()
{
    delete[] m_generationBuffer;
}

void ModuleOut::initialize(SynthProFactory* factory)
{
    m_generationBuffer = new char[Buffer::DEFAULT_LENGTH];

    for (int i = 0; i < Buffer::DEFAULT_LENGTH; i++) {
        m_generationBuffer[i] = 0;
    }

    if (factory) {
        // Creation of an Input.
        m_inPort = factory->createInPortReplicable(this, "in");
        m_inports.append(m_inPort);

        // Register to a fast timer to the Clock.
        Clock& clock = Clock::instance();
        clock.registerFastClock(this);
    }
}

// void ModuleOut::setSoundManagement(bool state)
// {
//     m_manageSound = state;
// }

void ModuleOut::timerExpired()
{
    // if (!m_manageSound) {
    //     return;
    // }

    int fillCounter = 0;
    qint64 sizeWritten = 1;
    int nbBytesNeededByOutput = m_audioOutput->bytesFree();

    while (((fillCounter < FILL_COUNTER_MAX) && (nbBytesNeededByOutput > 0)) && (sizeWritten > 0)) {
        // qWarning() << "Needing " << nbBytesNeededByOutput << ". Counter = " << fillCounter;
        // Check if we have some generated bytes left in order to feed the output.
        if (m_nbGeneratedBytesRemaining > 0) {

            // We have some bytes left in our buffer. Is it enough ?
            if (m_nbGeneratedBytesRemaining >= nbBytesNeededByOutput) {
                // We have more than enough. We send only what is needed.
                // qWarning() << "Trying to write : " << nbBytesNeededByOutput;
                sizeWritten = m_device->write(m_generationBuffer + m_generationBufferIndex, nbBytesNeededByOutput);
            } else {
                // We don't have enough. We send what we have for now.
                // qWarning() << "Trying to write : " << m_nbGeneratedBytesRemaining;
                sizeWritten = m_device->write(m_generationBuffer + m_generationBufferIndex, m_nbGeneratedBytesRemaining);
            }

            m_generationBufferIndex += sizeWritten;
            m_nbGeneratedBytesRemaining -= sizeWritten;

            nbBytesNeededByOutput = m_audioOutput->bytesFree();
        } else {
            // We don't have any bytes in our buffer. We need to generate data.
            // We call the sequencer for it to process all the modules.
            m_sequencer.process();

            // Now we copy our InPort to the generationBuffer. A conversion is needed.
            qreal* data = m_inPort->buffer()->data();

            for (int i = 0, size = m_inPort->buffer()->length(); i < size; i += 2) {
                int nb = (int)(data[i] / VCO::SIGNAL_INTENSITY * SIGNAL_OUT_UNSIGNED_INTENSITY);
                // FIXME : Works, but can't understand why. The output seems to be 8 bits only.
                m_generationBuffer[i] = 0; // nb / 256;
                m_generationBuffer[i + 1] = nb; // nb & 255;
            }

            m_generationBufferIndex = 0;
            m_nbGeneratedBytesRemaining = Buffer::DEFAULT_LENGTH;
        }

        fillCounter++;
    }

    /*
    if (fillCounter >= FILL_COUNTER_MAX) {
        qWarning() << "Unable to feed the sound card enough !";
    }
    if (sizeWritten == 0) {
        qWarning() << "Size written = 0... Abnormal.";
    }
    if (sizeWritten < 0) {
        qWarning() << "Error while writing to the sound card !";
    }
    */
}

void ModuleOut::ownProcess()
{
}
