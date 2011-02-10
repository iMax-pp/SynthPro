#include "abstraction/testaudiodeviceprovider.h"
#include "abstraction/testinport.h"
#include "abstraction/testmodulebufferrecorder.h"
#include "abstraction/testoutport.h"
#include "abstraction/testsequencer.h"
#include "abstraction/testvca.h"
#include "abstraction/testvcf.h"
#include "abstraction/testvco.h"
#include "abstraction/testlfo.h"
#include "abstraction/testwavegeneratorempty.h"
#include "abstraction/testwavegeneratorsaw.h"
#include "abstraction/testwavegeneratorsinus.h"
#include "abstraction/testwavegeneratorsquare.h"
#include "abstraction/testwavegeneratortriangle.h"

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

    TestVCA testVCA;
    QTest::qExec(&testVCA);

    TestWaveGeneratorEmpty testWaveGeneratorEmpty;
    QTest::qExec(&testWaveGeneratorEmpty);

    TestWaveGeneratorTriangle testWaveGeneratorTriangle;
    QTest::qExec(&testWaveGeneratorTriangle);

    TestWaveGeneratorSquare testWaveGeneratorSquare;
    QTest::qExec(&testWaveGeneratorSquare);

    TestWaveGeneratorSaw testWaveGeneratorSaw;
    QTest::qExec(&testWaveGeneratorSaw);

    TestWaveGeneratorSinus testWaveGeneratorSinus;
    QTest::qExec(&testWaveGeneratorSinus);

    TestAudioDeviceProvider testAudioDeviceProvider;
    QTest::qExec(&testAudioDeviceProvider);

    TestModuleBufferRecorder testModuleBufferRecorder;
    QTest::qExec(&testModuleBufferRecorder);

    TestVCF testVCF;
    QTest::qExec(&testVCF);

    TestLFO testLFO;
    QTest::qExec(&testLFO);
}
