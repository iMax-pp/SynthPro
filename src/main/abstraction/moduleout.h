#ifndef MODULEOUT_H
#define MODULEOUT_H

#include "module.h"

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
      * FIXME : not very good. Only to prevent triggering the Sequencer BEFORE
      * we have time to add the module to the SynthPro.
      */
    void setSoundManagement(bool);

    /**
      * Process the input signal.
      */
    void ownProcess(); // *** Probably virtual

public slots:
    virtual void timerExpired();

private:
    static const int GENERATION_BUFFER_SIZE = 900; //900;  // This must be small, but not too much (overhead).
    static const int FILL_COUNTER_MAX = 10;

    QIODevice* m_device;
    InPort* m_inPort;
    QAudioOutput* m_audioOutput;

    char* m_generationBuffer; // Fixed size (small), will feed the output buffer.
    char* m_generationBufferPointer; // Points where we are inside the generation buffer.
    int m_nbGeneratedBytesRemaining; // Indicates how many bytes of the generated buffer are still unused.

    Sequencer& m_sequencer;
    bool m_manageSound; // *** FIXME *** Not fond of it...
};

#endif // MODULEOUT_H
