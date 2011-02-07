#include "testwavegeneratorempty.h"

#include "src/main/abstraction/buffer.h"
#include "src/main/abstraction/wavegeneratorempty.h"

#include <QtTest/QTest>

void TestWaveGeneratorEmpty::testWaveGeneratorEmpty()
{
    WaveGeneratorEmpty* generator = new WaveGeneratorEmpty();
    Buffer* bufferOut = new Buffer(BUFFER_LENGTH);

    generator->generate(0, bufferOut); // We know we don't need a bufferIn.

    bool result = true;
    int i = 0;
    while (result && (i < BUFFER_LENGTH)) {
        result = (bufferOut->data()[i] == 0);
        i++;
    }

    QVERIFY(result);

    delete bufferOut;
    delete generator;
}
