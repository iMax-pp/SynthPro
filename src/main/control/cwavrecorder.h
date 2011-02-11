#ifndef CWAVRECORDER_H
#define CWAVRECORDER_H

#include "abstraction/module/wavrecorder.h"
#include "control/cmodule.h"

class CWavRecorder : public WavRecorder, public CModule {
public:
    CWavRecorder(SynthPro*, QString fileName = "output.wav", int nbProcessingBeforeSaving = 5);

    void initialize(SynthProFactory*);
};

#endif // CWAVRECORDER_H
