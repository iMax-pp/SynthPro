#ifndef ADSR_H
#define ADSR_H

#include "abstraction/module.h"

class InPort;
class OutPort;
class Dimmer;
class SynthProFactory;

class ADSR : public virtual Module {
    Q_OBJECT
public:
    ADSR(QObject* parent = 0);
    void initialize(SynthProFactory*);
    void ownProcess();

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

    InPort* m_gate;
    OutPort* m_outPort;

    Dimmer* m_attackDimmer;
    Dimmer* m_decayDimmer;
    Dimmer* m_sustainDimmer;
    Dimmer* m_releaseDimmer;
};

#endif // ADSR_H