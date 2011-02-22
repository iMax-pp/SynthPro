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

    static const int SAMPLER_MAX_DURATION = 500;

protected slots:
    void startRecording();
    void stopRecording();
    void startPlaying();

signals:
    void valueChanged(int);
    void lengthChanged(int);

protected:
    static const int NB_VALUES_CHANGED_BEFORE_EMIT_VALUECHANGED = 2000; // Allow to limit sending to the UI.

    InPort* m_inPort;
    InPort* m_gate;
    OutPort* m_outPort;
    Dimmer* m_bpmDimmer;
    PushButton* m_recordButton;
    PushButton* m_stopButton;
    PushButton* m_playButton;

    /// buffer where is saved the sample. Its size is a number of buffers
    Buffer* m_buffer;

    /// current index read or write in the class buffer.
    int m_bufferIndex;

    /// size of the sample in sample
    int m_sampleSize;

    /// state of the current value of the gate buffer
    bool m_gateState;
    bool m_oldGateState;

    /// current state of the module
    SamplerState m_state;

    /// index readed in the buffer while playing
    qreal m_positionInBuffer;

    /// index when sample really start ie whenits value is not 0
    int m_sampleStart;

    static const qreal MIN_BPM = -2;
    static const qreal MAX_BPM = 2;
    static const qreal DEFAULT_BPM = 1;

    /// initialize or reinitialize the buffer for a new record.
    void initializeBuffer();

    /// clean a buffer by setting all its value at 0.
    void purgeBuffer(Buffer*);
};

#endif // SAMPLER_H
