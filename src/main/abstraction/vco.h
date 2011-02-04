#ifndef VCO_H
#define VCO_H

#include "abstraction/inport.h"
#include "abstraction/module.h"
#include "abstraction/outport.h"

class WaveGenerator;

class VCO : public Module {
    Q_OBJECT

public:
    VCO(QObject* parent = 0);
    ~VCO();

    /**
     * Process its job : put a buffer in its outPort
     */
    void process();

    /**
     * Set the WaveGenerator of this VCO.
     * The VCO will then take care of deleting it.
     * @param generator a wave generator (Strategy design pattern)
     */
    void setWaveGenerator(WaveGenerator*);

    static const qreal SIGNAL_INTENSITY = 20000;
    static const qreal F0 = 261.626; // Frequency of the C4.
    static const qreal REPLAY_FREQUENCY = 44100; // We consider it won't change.

protected:

    WaveGenerator* m_waveGenerator;
    InPort m_vfm;
    OutPort m_out;

    /*
     * Initialization of the VCO
     */
    void init();
};

#endif // VCO_H
