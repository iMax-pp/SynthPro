#include "filterincrement.h"

FilterIncrement::FilterIncrement()
{
}

void FilterIncrement::apply(float* bufferIn, float* bufferOut, int bufferLength)
{
    for (int i = 0; i < bufferLength; i++) {
        int a = bufferIn[i];
        bufferOut[i] = (a > 0 ? ++a : --a);
    }

}
