#ifndef WAVEGENERATORSQUARE_H
#define WAVEGENERATORSQUARE_H

#include "abstraction/wavegenerator.h"

/**
  * Square Wave Generator, produces a square sound.
  */
class WaveGeneratorSquare : public WaveGenerator
{
public:
    WaveGeneratorSquare();

    /**
      * Generate a square wave.
      */
    virtual void generate(const Buffer* bufferIn, Buffer* bufferOut);

private:
    static const int SIGNAL_INTENSITY = 20000;

    int m_intensity;
    int m_currentStep;
    int m_currentFrequency; // Changes over time according to what is
                            // read in the bufferIn.
};

#endif // WAVEGENERATORSQUARE_H
