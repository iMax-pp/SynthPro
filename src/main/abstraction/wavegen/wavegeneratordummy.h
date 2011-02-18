#ifndef WAVEGENERATORDUMMY_H
#define WAVEGENERATORDUMMY_H

#include "abstraction/wavegen/wavegenerator.h"

/**
 * Dummy Wave Generator, produces a simple square sound with a fixed frequency.
 * This is useful to test the modules.
 */
class WaveGeneratorDummy : public WaveGenerator {
public:
    WaveGeneratorDummy();

    /**
     * Generate a square wave, with a fixed frequency. The bufferIn is ignored.
     */
    virtual void generate(const Buffer* bufferIn, Buffer* bufferOut);

private:
    static const int FIXED_PERIOD = 80;
    int m_intensity;
    int m_currentStep;
};

#endif // WAVEGENERATORDUMMY_H
