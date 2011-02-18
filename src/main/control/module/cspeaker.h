#ifndef CSPEAKER_H
#define CSPEAKER_H

#include "abstraction/module/speaker.h"
#include "control/cmodule.h"

/**
 * Speaker control class (PAC by inheritance).
 */
class CSpeaker : public Speaker, public CModule {
public:
    explicit CSpeaker(SynthPro*, QIODevice*, QAudioOutput*);

    void initialize(SynthProFactory*);
};

#endif // CSPEAKER_H
