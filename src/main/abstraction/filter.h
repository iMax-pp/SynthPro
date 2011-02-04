#ifndef FILTER_H
#define FILTER_H

class Buffer;

/**
  * Pure virtual class for the VCF to filter signals from an input buffer
  * to an output buffer.
  */
class Filter {
public:
    Filter() {}

    virtual void apply(Buffer* bufferIn, Buffer* bufferOut) = 0;
};

#endif // FILTER_H
