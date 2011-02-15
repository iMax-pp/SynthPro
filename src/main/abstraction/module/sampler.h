#ifndef SAMPLER_H
#define SAMPLER_H

#include "abstraction/module.h"

class Buffer;
class InPort;
class OutPort;
class Dimmer;
class PushButton;
class SynthProFactory;

/// TODO : implements gate and comment !
class Sampler : public virtual Module {
    Q_OBJECT

public:
    explicit Sampler(SynthPro*);
    virtual ~Sampler();
    void initialize(SynthProFactory*);

    /// Process its job(s) : record a sample, play a sample
    void ownProcess();


    enum SamplerState {
        EMPTY,
        RECORDING,
        PLAYING,
        WAITING
    };
    /// Only for mise au point

    QString state();

protected:
    static const int SAMPLER_MAX_DURATION = 5;

    InPort* m_inPort;
    InPort* m_gate;
    OutPort* m_outPort;
    Dimmer* m_bpmDimmer;
    PushButton* m_record;
    PushButton* m_stop;
    PushButton* m_play;
    Buffer* m_buffer;
    int m_bufferIndex;
    int m_sampleSize;


    SamplerState m_state;

    static const qreal MIN_BPM = 30;
    static const qreal MAX_BPM = 300;
    static const qreal DEFAULT_BPM = 80;

    void initializeBuffer();
};

#endif // SAMPLER_H
