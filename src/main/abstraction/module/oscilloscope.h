#ifndef OSCILLOSCOPE_H
#define OSCILLOSCOPE_H

#include "abstraction/module.h"

class InPort;
class SynthPro;
class SynthProFactory;

class Oscilloscope : public virtual Module {
    Q_OBJECT

public:
    Oscilloscope(SynthPro*);
    virtual ~Oscilloscope();

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
    InPort* m_inPort;
};

#endif // OSCILLOSCOPE_H
