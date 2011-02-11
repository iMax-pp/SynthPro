#ifndef CWAVRECORDER_H
#define CWAVRECORDER_H

#include "abstraction/wavrecorder.h"
#include "control/cmodule.h"

class CWavRecorder : public WavRecorder, public CModule {
public:
    explicit CWavRecorder(SynthPro*, QString fileName = "output.wav", int nbProcessingBeforeSaving = 5);
    
    void initialize(SynthProFactory*);    
};

#endif // CWAVRECORDER_H
