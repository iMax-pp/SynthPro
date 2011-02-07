#ifndef MODULEOUT_H
#define MODULEOUT_H

#include "module.h"

class InPort;
class SynthProFactory;
class QIODevice;

/**
  * Module that send its In buffer to the audio sound card.
  * At the instanciation, it requests a device to the AudioDeviceProvider.
  * It will fail if the device is used by another module.
  *
  * It must also register to a Clock in order call the Sequencer.
  * ???? WHO should call the Sequencer ?????
  */
class ModuleOut : public Module {
public:
    ModuleOut(QIODevice*, SynthProFactory* = 0, QObject* parent = 0);
    virtual ~ModuleOut();

    /**
      * Instanciate the ports. Used by the factory.
      */
    void initialize(); // *** Probably virtual

    /**
      * Process the input signal.
      */
    void ownProcess(); // *** Probably virtual

private:
    QIODevice* m_device;
    SynthProFactory* m_factory;
    InPort* m_inPort;
};

#endif // MODULEOUT_H
