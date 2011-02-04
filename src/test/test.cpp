#include "abstraction/testinport.h"
#include "abstraction/testoutport.h"

int main()
{
    TestInPort testInPort;
    QTest::qExec(&testInPort);

    TestOutPort testOutPort;
    QTest::qExec(&testOutPort);
}
