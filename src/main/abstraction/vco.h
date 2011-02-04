#ifndef VCO_H
#define VCO_H

#include "module.h"

class WaveGenerator;

class VCO : public Module {
    Q_OBJECT
public:
    VCO(QObject* parent = 0);
/**
* Process its job : put a buffer in its outPort
*/
    virtual void process();
/**
* @return his require module outputs.
*/
    virtual QList<Module*>::const_iterator getReguirements() const;
/**
* @param a wave generator (Strategy design pattern)
*/
    virtual void setWaveGenerator(WaveGenerator*);

    static const qreal SIGNAL_INTENSITY = 20000;
    static const qreal F0 = 261.626; // Frequency of the C4.
    static const qreal REPLAY_FREQUENCY = 44100; // We consider it won't change.

protected:

    WaveGenerator* m_waveGenerator;
    InPort* m_defaultInPort;
    OutPort* m_defaultOutPort;
/*
* Initialization of the VCO
*/
    virtual void init();
};

#endif // VCO_H
