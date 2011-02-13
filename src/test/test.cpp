#include "abstraction/module/testadsr.h"
#include "abstraction/module/testdelay.h"
#include "abstraction/module/testlfo.h"
#include "abstraction/module/testvca.h"
#include "abstraction/module/testvcf.h"
#include "abstraction/module/testvco.h"
#include "abstraction/module/testwavrecorder.h"
#include "abstraction/testaudiodeviceprovider.h"
#include "abstraction/testinport.h"
#include "abstraction/testoutport.h"
#include "abstraction/testsequencer.h"
#include "abstraction/wavegen/testwavegeneratorempty.h"
#include "abstraction/wavegen/testwavegeneratorsaw.h"
#include "abstraction/wavegen/testwavegeneratorsinus.h"
#include "abstraction/wavegen/testwavegeneratorsquare.h"
#include "abstraction/wavegen/testwavegeneratortriangle.h"

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

    TestADSR testADSR;
    QTest::qExec(&testADSR);

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

    TestWavRecorder testWavRecorder;
    QTest::qExec(&testWavRecorder);

    TestVCF testVCF;
    QTest::qExec(&testVCF);

    TestLFO testLFO;
    QTest::qExec(&testLFO);

    TestDelay testDelay;
    QTest::qExec(&testDelay);
}
