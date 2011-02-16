#ifndef CSAMPLER_H
#define CSAMPLER_H

#include "abstraction/module/sampler.h"
#include "control/cmodule.h"

class CSampler : public Sampler, public CModule {
    Q_OBJECT
    
public:
    explicit CSampler(SynthPro*);

    void initialize(SynthProFactory*);
    
protected slots:
    void startRecording();
    void stopRecording();
    void startPlaying();
};

#endif // CSAMPLER_H
