#ifndef VCO_H
#define VCO_H

#include "abstraction/inport.h"
#include "abstraction/module.h"
#include "abstraction/outport.h"
#include "audiodeviceprovider.h"

class WaveGenerator;
class SynthProFactory;
class Dimmer;
class Selector;

class VCO : public virtual Module {
    Q_OBJECT

public:
    VCO(QObject* parent = 0);
    virtual ~VCO();

    // Initialize the VCO (creates its ports using the factory)
    virtual void init(SynthProFactory*);

    /**
     * Process its job : put a buffer in its outPort
     */
    void ownProcess();

    /**
     * Set the WaveGenerator of this VCO.
     * The VCO will then take care of deleting it.
     * @param generator a wave generator (Strategy design pattern)
     */
    void setWaveGenerator(WaveGenerator*);

    Dimmer* dimmer();

    static const qreal SIGNAL_INTENSITY = 20000;
    static const qreal F0 = 261.626; // Frequency of the C4.
    static const qreal REPLAY_FREQUENCY = AudioDeviceProvider::OUTPUT_FREQUENCY;

protected:

    WaveGenerator* m_waveGenerator;
    InPort* m_vfm;
    OutPort* m_out;
    Selector* m_shapeSelector;
    Dimmer* m_kDimmer;

    static const qreal K_MIN = -5;
    static const qreal K_MAX = 5;
    static const qreal K_DEFAULT = 0;
};

#endif // VCO_H
