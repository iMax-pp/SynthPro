#include "wavegeneratorsquare.h"

#include "abstraction/vco.h"
#include "buffer.h"

#include <QtCore/qmath.h>

WaveGeneratorSquare::WaveGeneratorSquare()
    : m_intensity(VCO::SIGNAL_INTENSITY)
    , m_currentStep(0)
    , m_maximumStep(100)
    , m_currentSignalTension(0)
{
}

void WaveGeneratorSquare::generate(const Buffer* bufferIn, Buffer* bufferOut)
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
            qreal frequency = VCO::F0 * qPow(2, val);

            // Calculate the step of the frequency. *2 because we need
            // to find a period incorporates two phases.
            m_maximumStep = VCO::REPLAY_FREQUENCY / (frequency * 2);
        }

        m_currentStep++;
        if (m_currentStep >= m_maximumStep) {
            m_currentStep -= m_maximumStep;
        }

        dataOut[i] = m_intensity;
    }
}
