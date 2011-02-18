#ifndef WAVEGENERATOR_H
#define WAVEGENERATOR_H

class Buffer;

/**
 * Pure virtual class for the VCO to generate data from
 * an input buffer to an output buffer.
 */
class WaveGenerator {
public:
    inline WaveGenerator() {}

    /**
     * Generate the waveform, from a BufferIn, to a Bufferout.
     */
    virtual void generate(const Buffer* bufferIn, Buffer* bufferOut) = 0;
};


#endif // WAVEGENERATOR_H
