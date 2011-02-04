#ifndef FILTER_H
#define FILTER_H

/**
  * Pure virtual class for the VCF to filter signals from an input buffer
  * to an output buffer.
  */
class Filter
{
public:
    Filter() {}

    virtual void apply(float* bufferIn, float* bufferOut, int bufferLength) = 0;
};

#endif // FILTER_H
