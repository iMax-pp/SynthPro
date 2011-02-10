#ifndef CMODULEOUT_H
#define CMODULEOUT_H

#include "abstraction/moduleout.h"
#include "control/cmodule.h"

class CModuleOut : public ModuleOut, public CModule {
public:
    CModuleOut(SynthPro*, QIODevice*, QAudioOutput*);

    void initialize(SynthProFactory*);
};

#endif // CMODULEOUT_H
