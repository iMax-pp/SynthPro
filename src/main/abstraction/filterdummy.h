#ifndef FILTERDUMMY_H
#define FILTERDUMMY_H

#include "abstraction/filter.h"

/**
  * Dummy Filter, simply copy the bufferIn to the bufferOut.
  * This is useful to test the modules.
  */
class FilterDummy : public Filter {
public:
    FilterDummy();

    virtual void apply(Buffer* bufferIn, Buffer* bufferOut);
};

#endif // FILTERDUMMY_H
