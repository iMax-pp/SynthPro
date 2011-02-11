#ifndef WAVEGENERATORSINUS_H
#define WAVEGENERATORSINUS_H

#include "abstraction/wavegen/wavegenerator.h"

#include <QtGlobal>

/**
  * Sinus Wave Generator, produces a sinus sound.
  */
class WaveGeneratorSinus : public WaveGenerator {
public:
    WaveGeneratorSinus();

    /**
      * Generate a saw wave.
      */
    virtual void generate(const Buffer* bufferIn, Buffer* bufferOut);

private:
    qreal m_currentSignalTension; // Changes over time according to what is read in the bufferIn.
    qreal m_frequency;
    int m_sampleIndex; // Used to manage previous offset in the sinus.
};

#endif // WAVEGENERATORSINUS_H
