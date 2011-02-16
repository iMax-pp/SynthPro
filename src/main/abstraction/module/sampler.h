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

    void startRecording();
    void stopRecording();
    void startPlaying();

    /// Process its job(s): record a sample, play a sample
    void ownProcess();

    enum SamplerState {
        EMPTY,
        RECORDING,
        PLAYING,
        WAITING
    };

    /// Only for mise au point
    QString state();
    Buffer* sampleBuffer();

    static const int SAMPLER_MAX_DURATION = 250;

signals:
    void valueChanged(int);

protected:
    InPort* m_inPort;
    InPort* m_gate;
    OutPort* m_outPort;
    Dimmer* m_bpmDimmer;

    /// buffer where is saved the sample. Its size is a number of buffers
    Buffer* m_buffer;

    /// current index read or write in the class buffer.
    int m_bufferIndex;

    /// size of the sample in sample
    int m_sampleSize;
    bool m_gateState;
    bool m_oldGateState;
    SamplerState m_state;

    static const qreal MIN_BPM = 30;
    static const qreal MAX_BPM = 300;
    static const qreal DEFAULT_BPM = 80;


    /// initialize or reinitialize the buffer for a new record.
    void initializeBuffer();
};

#endif // SAMPLER_H
