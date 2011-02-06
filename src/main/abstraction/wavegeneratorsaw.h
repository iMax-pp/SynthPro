#ifndef WAVEGENERATORSAW_H
#define WAVEGENERATORSAW_H

#include "abstraction/wavegenerator.h"

#include <QtGlobal>

/**
  * Triangle Wave Generator, produces a saw sound.
  */
class WaveGeneratorSaw : public WaveGenerator {
public:
    WaveGeneratorSaw();

    /**
      * Generate a saw wave.
      */
    virtual void generate(const Buffer* bufferIn, Buffer* bufferOut);

private:
    qreal m_slope; // Slope of the saw.
    qreal m_intensity; // Current intensity of our calculated signal.
    qreal m_currentSignalTension; // Changes over time according to what is
                                  // read in the bufferIn.
    const qreal m_minimumIntensity;
};

#endif // WAVEGENERATORSAW_H
