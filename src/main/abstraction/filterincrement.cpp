#include "filterincrement.h"

#include "buffer.h"

FilterIncrement::FilterIncrement()
{
}

void FilterIncrement::apply(Buffer* bufferIn, Buffer*, qreal, Buffer* bufferOut)
{
    qreal* dataOut = bufferOut->data();
    for (int i = 0, size = bufferOut->length(); i < size; i++) {
        qreal a = bufferIn->data()[i];
        dataOut[i] = (a >= 0 ? ++a : --a);
    }
}
