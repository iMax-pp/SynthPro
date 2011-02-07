#ifndef TESTAUDIODEVICEPROVIDER_H
#define TESTAUDIODEVICEPROVIDER_H

#include <QObject>

/**
  * Test Audio Device Provider.
  * We initialize the audio output, ask for a device, which should be returned,
  * and asking for another one should be refused. We release the device, and ask
  * for another one, which should be accepted.
  */
class TestAudioDeviceProvider : public QObject {
    Q_OBJECT

private slots:
    void testAudioDeviceProvider();
};

#endif // TESTAUDIODEVICEPROVIDER_H
