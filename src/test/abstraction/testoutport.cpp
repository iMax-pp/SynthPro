#include "testoutport.h"

#include "abstraction/outport.h"

void TestOutPort::testOut()
{
    OutPort outPort(0);
    QVERIFY(outPort.out());
    QVERIFY(outPort.buffer()->length() == 256);
}

// FIXME this test case seems a bit weak
void TestOutPort::testSwapBuffers()
{
    OutPort out(0);

    out.buffer()->data()[0] = 1;

    out.swapBuffers();

    QCOMPARE(out.buffer()->data()[0], 0.0);
}
