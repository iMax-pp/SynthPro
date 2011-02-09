#ifndef CMODULEOUT_H
#define CMODULEOUT_H

#include "abstraction/moduleout.h"
#include "control/cmodule.h"

class CModuleOut : public ModuleOut, public CModule {
public:
    CModuleOut(QIODevice*, QAudioOutput*, QObject* parent = 0);

    void initialize(SynthProFactory*);
};

#endif // CMODULEOUT_H
