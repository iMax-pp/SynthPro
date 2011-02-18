#ifndef WAVEGENERATOREMPTY_H
#define WAVEGENERATOREMPTY_H

#include "abstraction/wavegen/wavegenerator.h"

/**
 * Wave Generator that only produces an empty buffer.
 */
class WaveGeneratorEmpty : public WaveGenerator {
public:
    WaveGeneratorEmpty();

    /**
     * Generate an empty buffer. The bufferIn is ignored.
     */
    virtual void generate(const Buffer*, Buffer* bufferOut);
};

#endif // WAVEGENERATOREMPTY_H
