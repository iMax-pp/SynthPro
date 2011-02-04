#include "abstraction/testinport.h"
#include "abstraction/testoutport.h"
#include "abstraction/testvco.h"
int main()
{
    TestInPort testInPort;
    QTest::qExec(&testInPort);

    TestOutPort testOutPort;
    QTest::qExec(&testOutPort);

    TestVCO testVCO;
    QTest::qExec(&testVCO);
}
