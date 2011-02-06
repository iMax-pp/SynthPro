#ifndef WAVEGENERATORTRIANGLE_H
#define WAVEGENERATORTRIANGLE_H

#include "abstraction/wavegenerator.h"

#include <QtGlobal>

/**
  * Triangle Wave Generator, produces a triangle sound.
  */
class WaveGeneratorTriangle : public WaveGenerator {
public:
    WaveGeneratorTriangle();

    /**
      * Generate a triangle wave.
      */
    virtual void generate(const Buffer* bufferIn, Buffer* bufferOut);

private:
    qreal m_slope; // Slope of the triangle.
    qreal m_intensity; // Current intensity of our calculated signal.
    qreal m_currentSignalTension; // Changes over time according to what is
                                  // read in the bufferIn.
};

#endif // WAVEGENERATORTRIANGLE_H
