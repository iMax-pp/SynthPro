#include "wavegeneratortriangle.h"

#include "abstraction/buffer.h"
#include "abstraction/module/vco.h"

#include <QtCore/qmath.h>

WaveGeneratorTriangle::WaveGeneratorTriangle()
    : m_slope(0)
    , m_intensity(0)
    , m_currentSignalTension(-1000) // Unreachable value.
{
}

void WaveGeneratorTriangle::generate(const Buffer* bufferIn, Buffer* bufferOut)
{
    qreal* dataIn = bufferIn->data();
    qreal* dataOut = bufferOut->data();

    for (int i = 0, length = bufferOut->length(); i < length; i++) {

        // Test if the current frequency is the same as before.
        // If yes, recalculate the output frequency.
        qreal val = dataIn[i];

        if (m_currentSignalTension != val) {
            // Limit test
            val = val > INTENSITY_LIMIT ? INTENSITY_LIMIT : val;
            val = val < -INTENSITY_LIMIT ? -INTENSITY_LIMIT : val;

            m_currentSignalTension = val;
            // Convert a tension into a frequency.
            qreal frequency = VCO::F0 * qPow(2, val);


            // Calculate the step of the frequency. *4 because we need
            // to find a period that incorporates two phases, including
            // above and under the 0, and the "up" and "down" slope.
            qreal maximumStep = VCO::REPLAY_FREQUENCY / (frequency * 4);

            // Calculate the slope of the triangle.
            qreal newSlope = VCO::SIGNAL_INTENSITY / maximumStep;

            // In order to prevent clicks, make sure that our slope is in
            // the same "direction" as the previous one.
            m_slope = (m_slope < 0 ? -newSlope : newSlope);
        }

        // Check if our intensity is above/below the maximum intensity.
        // If yes, invert the slope.
        if (qAbs(m_intensity + m_slope) > VCO::SIGNAL_INTENSITY) {
            m_slope = -m_slope;
        }

        m_intensity += m_slope;

        dataOut[i] = m_intensity;
    }
}
