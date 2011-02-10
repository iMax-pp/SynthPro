#include "testoutport.h"

#include "abstraction/outport.h"

void TestOutPort::testOut()
{
    OutPort outPort(0, "out");
    QVERIFY(outPort.out());
    QVERIFY(outPort.buffer()->length() == Buffer::DEFAULT_LENGTH);
}
