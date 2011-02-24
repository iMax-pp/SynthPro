#ifndef FILTER_H
#define FILTER_H

class Buffer;

#include <QtCore>

/**
  * Pure virtual class for the VCF to filter signals from an input buffer
  * to an output buffer. It also require another buffer for the CutOff Frequency,
  * as well as the Resonance dimmer value.
  */
class Filter {
public:
    Filter() {}

    virtual void apply(Buffer* bufferIn, Buffer* bufferInCutOff, qreal cutOffBase, qreal resonance, Buffer* bufferOut) = 0;

protected:
    static const int INTENSITY_LIMIT = 15; // Safety, especially useful with looping modules.
};

#endif // FILTER_H
