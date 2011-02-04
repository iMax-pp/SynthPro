#include "abstraction/testinport.h"
#include "abstraction/testoutport.h"
#include "abstraction/testsequencer.h"

int main()
{
    TestInPort testInPort;
    QTest::qExec(&testInPort);

    TestOutPort testOutPort;
    QTest::qExec(&testOutPort);

    TestSequencer testSequencer;
    QTest::qExec(&testSequencer);
}
