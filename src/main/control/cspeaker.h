#ifndef CSPEAKER_H
#define CSPEAKER_H

#include "abstraction/speaker.h"
#include "control/cmodule.h"

class CSpeaker : public Speaker, public CModule {
public:
    CSpeaker(SynthPro*, QIODevice*, QAudioOutput*);

    void initialize(SynthProFactory*);
};

#endif // CSPEAKER_H
