#include "filterdummy.h"

#include "buffer.h"

#include <QtCore>

FilterDummy::FilterDummy()
{
}

void FilterDummy::apply(Buffer* bufferIn, Buffer*, qreal, Buffer* bufferOut)
{
    memcpy(bufferOut->data(), bufferIn->data(), bufferOut->length() * sizeof(*bufferIn->data()));
}
