#ifndef COSCILLOSCOPE_H
#define COSCILLOSCOPE_H

#include "abstraction/moduleoscilloscope.h"
#include "control/cmodule.h"

class COscilloscope : public ModuleOscilloscope, public CModule {

public:
    explicit COscilloscope(SynthPro*);

    void initialize(SynthProFactory*);
};

#endif // COSCILLOSCOPE_H
