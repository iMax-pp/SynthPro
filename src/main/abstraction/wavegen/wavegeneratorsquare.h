#ifndef WAVEGENERATORSQUARE_H
#define WAVEGENERATORSQUARE_H

#include "abstraction/wavegen/wavegenerator.h"

#include <QtGlobal>

/**
  * Square Wave Generator, produces a square sound.
  */
class WaveGeneratorSquare : public WaveGenerator {
public:
    WaveGeneratorSquare();

    /**
      * Generate a square wave.
      */
    virtual void generate(const Buffer* bufferIn, Buffer* bufferOut);

private:
    qreal m_intensity;
    qreal m_currentStep;
    qreal m_maximumStep;
    qreal m_currentSignalTension; // Changes over time according to what is read in the bufferIn.
};

#endif // WAVEGENERATORSQUARE_H
