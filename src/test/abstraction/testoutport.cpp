#include "testoutport.h"

#include "abstraction/outport.h"

void TestOutPort::testOut()
{
    OutPort outPort;
    QVERIFY(outPort.out());
}
