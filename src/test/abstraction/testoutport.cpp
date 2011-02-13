#include "testoutport.h"

#include "abstraction/component/outport.h"
#include "factory/simplefactory.h"

void TestOutPort::testOut()
{
    SimpleFactory factory;
    OutPort* outPort = factory.createOutPort(0, "out");

    QVERIFY(outPort->out());
    QVERIFY(outPort->buffer()->length() == Buffer::DEFAULT_LENGTH);

    delete outPort;
}
