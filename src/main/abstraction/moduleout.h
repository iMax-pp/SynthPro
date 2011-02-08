#ifndef MODULEOUT_H
#define MODULEOUT_H

#include "module.h"

#include <QObject>

class InPort;
class QAudioOutput;
class QIODevice;
class SynthProFactory;

/**
  * Module that send its In buffer to the audio sound card.
  * At the instanciation, it requests a device to the AudioDeviceProvider.
  * It will fail if the device is used by another module.
  *
  * It must also register to a Clock in order call the Sequencer.
  * ???? WHO should call the Sequencer ?????
  */
class ModuleOut : public Module {
    // Q_OBJECT
public:
    ModuleOut(QIODevice*, QAudioOutput*, QObject* parent = 0);
    virtual ~ModuleOut();

    /**
      * Instanciate the ports. Used by the factory.
      */
    void initialize(SynthProFactory* = 0); // *** Probably virtual

    /**
      * Process the input signal.
      */
    void ownProcess(); // *** Probably virtual

public slots:
    virtual void timerExpired();

private:
    QIODevice* m_device;
    InPort* m_inPort;
    QAudioOutput* m_audioOutput;
};

#endif // MODULEOUT_H
