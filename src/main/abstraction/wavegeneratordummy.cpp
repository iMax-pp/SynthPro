#include "wavegeneratordummy.h"

WaveGeneratorDummy::WaveGeneratorDummy()
    : m_intensity(SIGNAL_INTENSITY)
    , m_currentStep(0)
{
}

void WaveGeneratorDummy::generate(const float*, float* bufferOut, int bufferLength, float)
{
    for (int i = 0; i < bufferLength; i++) {
        if (++m_currentStep > FIXED_PERIOD) {
            m_intensity = -m_intensity;
            m_currentStep = 0;
        }

        bufferOut[i] = m_intensity;
    }
}
