#ifndef FILTERDUMMY_H
#define FILTERDUMMY_H

#include "abstraction/filter.h"

/**
  * Dummy Filter, simply copy the bufferIn to the bufferOut.
  * This is useful to test the modules.
  */
class FilterDummy : public Filter
{
public:
    FilterDummy();

    virtual void apply(float* bufferIn, float* bufferOut, int bufferLength);
};

#endif // FILTERDUMMY_H
