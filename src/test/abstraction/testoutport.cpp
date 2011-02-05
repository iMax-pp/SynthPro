#include "testoutport.h"

#include "abstraction/outport.h"

void TestOutPort::testOut()
{
    OutPort outPort(0);
    QVERIFY(outPort.out());
    QVERIFY(outPort.buffer()->length() == 256);
}
