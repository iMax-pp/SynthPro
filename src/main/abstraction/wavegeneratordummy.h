#ifndef WAVEGENERATORDUMMY_H
#define WAVEGENERATORDUMMY_H

#include "abstraction/wavegenerator.h"

/**
  * Dummy Wave Generator, produces a simple square sound with a fixed frequency.
  * This is useful to test the modules.
  */
class WaveGeneratorDummy : public WaveGenerator
{
public:
    WaveGeneratorDummy();
    virtual void generate(const float* bufferIn, float* bufferOut, int bufferLength, float frequency);

private:
    static const int FIXED_PERIOD = 80;
    static const int SIGNAL_INTENSITY = 20000;

    int m_intensity;
    int m_currentStep;
};

#endif // WAVEGENERATORDUMMY_H
