#ifndef VCO_H
#define VCO_H

#include "QHash"
#include "abstraction/inport.h"
#include "abstraction/module.h"
#include "abstraction/outport.h"
#include "audiodeviceprovider.h"
#include "factory/wavegeneratorfactory.h"


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
    virtual void initialize(SynthProFactory*);

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

    /**
    * @return value of the current value of the dimmer
    */
    qreal k() const;

    /**
    * set the value of the dimmer
    */
    void setK(qreal value);

    static const qreal SIGNAL_INTENSITY = 5;
    static const qreal F0 = 261.626; // Frequency of the C4.
    static const qreal REPLAY_FREQUENCY = AudioDeviceProvider::OUTPUT_FREQUENCY;

public slots :

    void waveShapeChanged(int);

protected:
    WaveGenerator* m_waveGenerator;
    InPort* m_vfm;
    OutPort* m_out;
    Selector* m_shapeSelector;
    Dimmer* m_kDimmer;
    WaveGeneratorFactory* m_waveGeneratorFactory;
    QHash<int, WaveGeneratorFactory::WaveType>* m_selectorConversionMap;
    QList<int> m_selectorValueList;

    static const qreal K_MIN = -5;
    static const qreal K_MAX = 5;
    static const qreal K_DEFAULT = 0;
};

#endif // VCO_H
