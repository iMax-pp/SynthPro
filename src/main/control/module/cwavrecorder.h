#ifndef CWAVRECORDER_H
#define CWAVRECORDER_H

#include "abstraction/module/wavrecorder.h"
#include "control/cmodule.h"

class CWavRecorder : public WavRecorder, public CModule {
public:
    CWavRecorder(SynthPro*, int nbProcessingBeforeSaving = 10);

    void initialize(SynthProFactory*);

public slots:
    void startNewFile();
};

#endif // CWAVRECORDER_H
