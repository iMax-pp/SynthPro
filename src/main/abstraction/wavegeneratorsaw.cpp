#include "wavegeneratorsaw.h"

#include "abstraction/vco.h"
#include "buffer.h"

#include <QtCore/qmath.h>

WaveGeneratorSaw::WaveGeneratorSaw()
    : m_slope(0)
    , m_intensity(0)
    , m_currentSignalTension(-1000)
    , m_minimumIntensity(VCO::SIGNAL_INTENSITY * -1)
{
}

void WaveGeneratorSaw::generate(const Buffer* bufferIn, Buffer* bufferOut)
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
            // to find a period that incorporates two periods
            // (below and above the 0).
            qreal maximumStep = VCO::REPLAY_FREQUENCY / (frequency * 2);

            // Calculate the slope of the saw.
            m_slope = VCO::SIGNAL_INTENSITY / maximumStep;
        }

        m_intensity -= m_slope;

        // Check if our intensity is below the minimum intensity.
        // If yes, set the intensity to its maximum.
        if (m_intensity < m_minimumIntensity) {
            m_intensity = VCO::SIGNAL_INTENSITY;
        }

        dataOut[i] = m_intensity;
    }
}
