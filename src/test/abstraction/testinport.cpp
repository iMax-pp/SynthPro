#include "testinport.h"

#include "abstraction/inport.h"

void TestInPort::testOut()
{
    InPort inPort;
    QVERIFY(!inPort.out());
}
