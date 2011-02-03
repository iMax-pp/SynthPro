#include "wavegeneratordummy.h"

WaveGeneratorDummy::WaveGeneratorDummy()
        : m_intensity(SIGNAL_INTENSITY)
        , m_currentStep(0)
{
}

/**
  * Generate a square wave, with a fixed frequency.
  */
void WaveGeneratorDummy::generate(const float*, float* bufferOut, int bufferLength, float)
{
    int i = 0;
    while (i < bufferLength) {
        if (++m_currentStep > FIXED_PERIOD) {
            m_intensity = -m_intensity;
            m_currentStep = 0;
        }
        bufferOut[i++] = m_intensity;
        bufferLength--;
    }
}
