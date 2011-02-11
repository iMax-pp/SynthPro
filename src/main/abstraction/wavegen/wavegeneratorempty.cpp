#include "wavegeneratorempty.h"

#include "abstraction/buffer.h"

WaveGeneratorEmpty::WaveGeneratorEmpty()
{
}

void WaveGeneratorEmpty::generate(const Buffer*, Buffer* bufferOut)
{
    for (int i = 0, length = bufferOut->length(); i < length; i++) {
        bufferOut->data()[i] = 0;
    }
}
