#include "wavegeneratorsinus.h"

#include "abstraction/vco.h"
#include "buffer.h"

#include <QtCore/qmath.h>

WaveGeneratorSinus::WaveGeneratorSinus()
    : m_currentSignalTension(-1000)
    , m_frequency(VCO::F0)
    , m_sampleIndex(0)
{
}

void WaveGeneratorSinus::generate(const Buffer* bufferIn, Buffer* bufferOut)
{
    qreal* dataIn = bufferIn->data();
    qreal* dataOut = bufferOut->data();

    for (int i = 0, length = bufferOut->length(); i < length; i++) {

        // Test if the current frequency is the same as before.
        // If yes, recalculate the output frequency.
        qreal val = dataIn[i];
        if (m_currentSignalTension != val) {
            m_currentSignalTension = val;
            // Convert a tension into a frequency.
            m_frequency = VCO::F0 * qPow(2, val);
        }

        // Calculate the sinus itself.
        qreal intensity = qSin(2 * M_PI * m_frequency * m_sampleIndex / VCO::REPLAY_FREQUENCY);
        intensity *= VCO::SIGNAL_INTENSITY;

        m_sampleIndex++; // The looping of this value may produce a small click,
                         // but it should happen very rarely.

        dataOut[i] = intensity;
    }
}
