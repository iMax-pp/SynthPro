#ifndef FILTERINCREMENT_H
#define FILTERINCREMENT_H

#include "abstraction/filter/filter.h"

/**
  * Dummy Filter that increments every value of the input buffer if >0,
  * decrements if <0, and copy them to the output buffer.
  * Especially used as a test.
  */
class FilterIncrement : public Filter {
public:
    FilterIncrement();

    virtual void apply(Buffer* bufferIn, Buffer* bufferInCutOff, qreal cutOffBase, qreal resonance, Buffer* bufferOut);

    static const qreal INCREMENT_VALUE = 0.1;
};

#endif // FILTERINCREMENT_H
