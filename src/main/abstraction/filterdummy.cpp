#include "filterdummy.h"

#include <QtCore>

#include "buffer.h"

FilterDummy::FilterDummy()
{
}

void FilterDummy::apply(Buffer* bufferIn, Buffer* bufferOut)
{
    memcpy(bufferOut->data(), bufferIn->data(), bufferOut->length());
}
