#ifndef MODULEOUT_H
#define MODULEOUT_H

#include "module.h"
#include "vco.h"

#include <QObject>

class InPort;
class QAudioOutput;
class QIODevice;
class Sequencer;
class SynthProFactory;

/**
  * Module that send its In buffer to the audio sound card.
  * At the instanciation, it requests a device to the AudioDeviceProvider.
  * It will fail if the device is used by another module.
  *
  * It must also register to a Clock, which will call the timerExpired Slot.
  * This will ask the sound card how many bytes it requires. If the internal
  * buffer of the module can provide it, it does. Else, it calls the
  * Sequencer, and copy the input of the module into the generation buffer.
  */
class ModuleOut : public virtual Module {
    // Q_OBJECT
public:
    static const int SIGNAL_OUT_UNSIGNED_INTENSITY = 127;

    ModuleOut(QIODevice*, QAudioOutput*, QObject* parent = 0);
    virtual ~ModuleOut();

    /**
      * Instanciate the ports. Used by the factory.
      */
    virtual void initialize(SynthProFactory*);

    /**
      * FIXME : not very good. Only to prevent triggering the Sequencer BEFORE
      * we have time to add the module to the SynthPro.
      */
    // void setSoundManagement(bool);

    /**
      * Process the input signal.
      */
    void ownProcess();

public slots:
    virtual void timerExpired();

protected:
    static const int FILL_COUNTER_MAX = 10;

    QIODevice* m_device;
    InPort* m_inPort;
    QAudioOutput* m_audioOutput;

    char* m_generationBuffer; // Fixed size (small), will feed the output buffer.
    int m_generationBufferIndex; // Index inside the generation buffer.
    int m_nbGeneratedBytesRemaining; // Indicates how many bytes of the generated buffer are still unused.

    Sequencer& m_sequencer;
    // bool m_manageSound; // *** FIXME *** Not fond of it...
};

#endif // MODULEOUT_H
