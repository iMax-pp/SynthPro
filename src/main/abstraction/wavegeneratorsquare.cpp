#include "wavegeneratorsquare.h"

#include "buffer.h"

WaveGeneratorSquare::WaveGeneratorSquare()
    : m_intensity(SIGNAL_INTENSITY)
    , m_currentFrequency(0)
{
}

void WaveGeneratorSquare::generate(const Buffer* bufferIn, Buffer* bufferOut)
{
    qreal* dataIn = bufferIn->data();
    qreal* dataOut = bufferOut->data();

    for (int i = 0, length = bufferOut->length(); i < length; i++) {
        // Test if the current frequency is the same as before.
        // If yes, recalculate the output frequency.
        if (m_currentFrequency != dataIn[i]) {
            // TODO : realculate frequency.
        }

        // TODO : check the frequency to invert the phase.

        dataOut[i] = m_intensity;
    }
}
