#include "filterdummy.h"

#include <QtCore>

FilterDummy::FilterDummy()
{
}

void FilterDummy::apply(float* bufferIn, float* bufferOut, int bufferLength)
{
    memcpy(bufferOut, bufferIn, bufferLength);
}
