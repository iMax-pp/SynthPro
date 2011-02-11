#ifndef COSCILLOSCOPE_H
#define COSCILLOSCOPE_H

#include "abstraction/oscilloscope.h"
#include "control/cmodule.h"

class COscilloscope : public Oscilloscope, public CModule {

public:
    explicit COscilloscope(SynthPro*);

    void initialize(SynthProFactory*);

    /**
      * Process the input signal.
      */
    virtual void ownProcess();
};

#endif // COSCILLOSCOPE_H
