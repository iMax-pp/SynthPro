#ifndef WAVEGENERATOR_H
#define WAVEGENERATOR_H

/**
  * Pure virtual class for the VCO to generate data from
  * an input buffer to an output buffer.
  */
class WaveGenerator {
public:
    WaveGenerator() {}

    virtual void generate(const float* bufferIn, float* bufferOut, int bufferLength, float frequency) = 0;
};


#endif // WAVEGENERATOR_H
