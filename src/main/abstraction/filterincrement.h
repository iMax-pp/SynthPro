#ifndef FILTERINCREMENT_H
#define FILTERINCREMENT_H

#include "abstraction/filter.h"

/**
  * Dummy Filter that increments every value of the input buffer if >0,
  * decrements if <0, and copy them to the output buffer.
  * Especially used as a test.
  */
class FilterIncrement : public Filter {
public:
    FilterIncrement();

    virtual void apply(float* bufferIn, float* bufferOut, int bufferLength);
};

#endif // FILTERINCREMENT_H
