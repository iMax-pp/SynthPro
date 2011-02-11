#ifndef MODULEKEYBOARD_H
#define MODULEKEYBOARD_H

#include "module.h"

class OutPort;
class SynthPro;
class SynthProFactory;

class ModuleKeyboard : public virtual Module {
    Q_OBJECT

public:
    ModuleKeyboard(SynthPro*);
    virtual ~ModuleKeyboard();

    /**
      * Instanciate the ports. Used by the factory.
      */
    virtual void initialize(SynthProFactory*);

    /**
      * Process the input signal.
      */
    virtual void ownProcess();

public slots:
    virtual void timerExpired();

protected:
    static const int VALUE_GATE_ON = 1;
    static const int VALUE_GATE_OFF = 0;
    static const int NUMBER_KEYS_IN_OCTAVE = 12;

    OutPort* m_outPortFrequency;
    OutPort* m_outPortGate;

    int m_keyPressedNumber;
    bool m_pressed;
};

#endif // MODULEKEYBOARD_H
