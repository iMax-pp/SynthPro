#include "abstraction/testinport.h"
#include "abstraction/testmodulebufferrecorder.h"
#include "abstraction/testoutport.h"
#include "abstraction/testsequencer.h"
#include "abstraction/testvco.h"
#include "abstraction/testwavegeneratorempty.h"

int main()
{
    TestInPort testInPort;
    QTest::qExec(&testInPort);

    TestOutPort testOutPort;
    QTest::qExec(&testOutPort);

    TestSequencer testSequencer;
    QTest::qExec(&testSequencer);

    TestVCO testVCO;
    QTest::qExec(&testVCO);

    TestWaveGeneratorEmpty testWaveGeneratorEmpty;
    QTest::qExec(&testWaveGeneratorEmpty);

    TestModuleBufferRecorder testModuleBufferRecorder;
    QTest::qExec(&testModuleBufferRecorder);
}
