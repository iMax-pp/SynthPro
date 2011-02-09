#ifndef VCA_H
#define VCA_H

#include "abstraction/module.h"

class InPort;
class OutPort;
class Dimmer;
class SynthProFactory;

/**
* This class amplify the signal it receive
*/
class VCA : public virtual Module {
    Q_OBJECT
public:
    VCA(QObject* parent = 0);
    void initialize(SynthProFactory*);


     /// Process its job : multiply the input buffer values
     void ownProcess();

    /// @return the gain of the VCA
    qreal gain();
    void setGain(qreal);


protected:
    static const qreal GAIN_MIN = 0;
    static const qreal GAIN_MAX = 2;
    static const qreal GAIN_DEFAULT = 1;

    InPort* m_input1;
    OutPort* m_output1;
    Dimmer* m_gain;
};

#endif // VCA_H
