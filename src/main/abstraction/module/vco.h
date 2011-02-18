#ifndef VCO_H
#define VCO_H

#include "abstraction/audiodeviceprovider.h"
#include "abstraction/module.h"

class InPort;
class OutPort;
class WaveGenerator;
class WaveGeneratorFactory;
class SynthProFactory;
class Dimmer;
class Selector;

class VCO : public virtual Module {
    Q_OBJECT

public:
    explicit VCO(SynthPro*);
    virtual ~VCO();

    // Initialize the VCO (creates its ports using the factory)
    virtual void initialize(SynthProFactory*);

    /**
     * Process its job : fill the BufferOut.
     */
    void ownProcess();

    /**
     * @return The current value of the dimmer.
     */
    qreal k() const;

    /**
     * Set the value of the dimmer.
     */
    void setK(qreal value);

    /**
     * @return The current wave shape selected, by its value on the selector himself.
     */
    QString shape();

    /**
     * Set the value of the selector indirectly : setting this value on the selector himself.
     */
    void setShape(QString);


    static const qreal SIGNAL_INTENSITY = 5;
    static const qreal F0 = 261.626; // Frequency of the C4.
    static const qreal REPLAY_FREQUENCY = AudioDeviceProvider::OUTPUT_FREQUENCY;

public slots :
    /**
    * Slot connected to a signal emitted by the selector to inform its value has changed.
    */
    void waveShapeChanged(int);

protected:
    WaveGenerator* m_waveGenerator;
    WaveGeneratorFactory* m_waveGeneratorFactory;

    InPort* m_vfm;
    OutPort* m_out;
    Selector* m_shapeSelector;
    Dimmer* m_kDimmer;

    static const qreal K_MIN = -5;
    static const qreal K_MAX = 5;
    static const qreal K_DEFAULT = 0;
};

#endif // VCO_H
