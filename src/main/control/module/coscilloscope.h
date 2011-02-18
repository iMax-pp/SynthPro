#ifndef COSCILLOSCOPE_H
#define COSCILLOSCOPE_H

#include "abstraction/module/oscilloscope.h"
#include "control/cmodule.h"

class COscilloscope : public Oscilloscope, public CModule {

public:
    explicit COscilloscope(SynthPro*);

    void initialize(SynthProFactory*);

    /**
     * Order the Presentation it has to refresh itself.
     */
    virtual void ownProcess();
};

#endif // COSCILLOSCOPE_H
