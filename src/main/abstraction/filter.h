#ifndef FILTER_H
#define FILTER_H

class Buffer;

#include <QtCore>

/**
  * Pure virtual class for the VCF to filter signals from an input buffer
  * to an output buffer. It also require another buffer for the CutOff Frequency,
  * as well as the Resonance dimmer value which may not be useful).
  */
class Filter {
public:
    Filter() {}

    virtual void apply(Buffer* bufferIn, Buffer* bufferInCutOff, qreal resonance, Buffer* bufferOut) = 0;
};

#endif // FILTER_H
