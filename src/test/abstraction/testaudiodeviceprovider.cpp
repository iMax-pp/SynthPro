#include "testaudiodeviceprovider.h"

#include "abstraction/audiodeviceprovider.h"

#include <QIODevice>
#include <QTest>

void TestAudioDeviceProvider::testAudioDeviceProvider()
{
    AudioDeviceProvider& adp = AudioDeviceProvider::instance();
    QVERIFY(adp.initializeAudioOutput());

    QIODevice* device = adp.device();
    QVERIFY(device != 0);

    QIODevice* notDevice = adp.device();
    QVERIFY(notDevice == 0);

    adp.releaseDevice();

    device = adp.device();
    QVERIFY(device != 0);

    adp.releaseDevice();
    adp.stop();
}
