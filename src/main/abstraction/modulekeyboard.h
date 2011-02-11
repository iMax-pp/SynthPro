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
    OutPort* m_outPortFrequency;
    OutPort* m_outPortGate;
};

#endif // MODULEKEYBOARD_H
