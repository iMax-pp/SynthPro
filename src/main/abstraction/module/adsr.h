#ifndef ADSR_H
#define ADSR_H

#include "abstraction/module.h"

class InPort;
class OutPort;
class Dimmer;
class PushButton;
class SynthProFactory;
/// A state pattern ?
class ADSR : public virtual Module {
    Q_OBJECT

public:
    explicit ADSR(SynthPro*);

    virtual void initialize(SynthProFactory*);
    void ownProcess();

    void setAttackValue(qreal);
    void setDecayValue(qreal);
    void setSustainValue(qreal);
    void setReleaseValue(qreal);

protected:

    static const qreal ATTACK_MIN = 0;
    static const qreal ATTACK_MAX = 2;
    static const qreal ATTACK_DEFAULT = 0.1;

    static const qreal DECAY_MIN = 0;
    static const qreal DECAY_MAX = 2;
    static const qreal DECAY_DEFAULT = 0.2;

    static const qreal SUSTAIN_MIN = 0;
    static const qreal SUSTAIN_MAX = 1;
    static const qreal SUSTAIN_DEFAULT = 0.5;

    static const qreal RELEASE_MIN = 0;
    static const qreal RELEASE_MAX = 1;
    static const qreal RELEASE_DEFAULT = 0.5;

    static const qreal GATE_LEVEL = 0.1;

    InPort* m_gate;
    OutPort* m_outPort;

    Dimmer* m_attackDimmer;
    Dimmer* m_decayDimmer;
    Dimmer* m_sustainDimmer;
    Dimmer* m_releaseDimmer;
    PushButton* m_manualControl;

    int m_timeLine;

    enum AdsrState {
        IDLE,
        ATTACK,
        DECAY,
        SUSTAIN,
        RELEASE,
    };

    AdsrState m_currentState;
    qreal m_gateValue;
    qreal m_startRelease;
    qreal m_currentGain;
};

#endif // ADSR_H
