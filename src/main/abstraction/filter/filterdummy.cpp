#include "filterdummy.h"

#include "abstraction/buffer.h"

#include <QtCore>

FilterDummy::FilterDummy()
{
}

void FilterDummy::apply(Buffer* bufferIn, Buffer*, qreal, qreal, Buffer* bufferOut)
{
    memcpy(bufferOut->data(), bufferIn->data(), bufferOut->length() * sizeof(*bufferIn->data()));
}
