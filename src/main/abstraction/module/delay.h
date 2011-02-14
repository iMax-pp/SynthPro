#ifndef DELAY_H
#define DELAY_H

#include "abstraction/module.h"

class Buffer;
class Dimmer;
class InPort;
class OutPort;
class SynthPro;
class SynthProFactory;


class Delay : public virtual Module {
    Q_OBJECT
public:
    explicit Delay(SynthPro*);
    virtual ~Delay();
    virtual void initialize(SynthProFactory*);
    void ownProcess();

    // only for testing, will be delete after
    Buffer* buffer1();

protected:

    InPort* m_inPort;
    OutPort* m_outPort;
    Buffer* m_buffer1;
    Buffer* m_buffer2;
    Buffer* m_buffer3;
    Dimmer* m_durationDimmer;
    Dimmer* m_decayDimmer;


    int m_delaySizeMax; /// max number  buffers in the buffer
    int m_readIndex, m_writeIndex, m_readIndex2, m_writeIndex2;


    static const qreal BUFFER_DURATION_MAX = 5;

    static const qreal DURATION_MIN = 0;
    static const qreal DURATION_MAX = 5;
    static const qreal DURATION_DEFAULT = 5;

    static const qreal DECAY_MIN = 0;
    static const qreal DECAY_MAX = 1;
    static const qreal DECAY_DEFAULT = 0.5;

};

#endif // DELAY_H
