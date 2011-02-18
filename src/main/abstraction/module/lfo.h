#ifndef LFO_H
#define LFO_H

#include "abstraction/audiodeviceprovider.h"
#include "abstraction/module.h"

class Buffer;
class InPort;
class OutPort;
class WaveGenerator;
class WaveGeneratorFactory;
class SynthProFactory;
class Dimmer;
class Selector;

/**
 * A LFO is a Low Frequency Oscillator.
 * It needs three parameters (dimmers) :
 * - k (low frequency).
 * - range (maximum intensity).
 * - offset (offset added to the range).
 */
class LFO : public virtual Module {
    Q_OBJECT

public:
    explicit LFO(SynthPro*);
    virtual ~LFO();

    // Initialize the LFO (creates its ports using the factory)
    virtual void initialize(SynthProFactory*);

    /**
     * Fill the outPort
     */
    void ownProcess();

    /**
     * @return The current value of the k dimmer
     */
    qreal k() const;

    /**
     * Set the value of the k dimmer
     */
    void setK(qreal value);

    /**
     * @return The current value of the Range dimmer
     */
    qreal range() const;

    /**
     * Set the value of the Range dimmer
     */
    void setRange(qreal value);

    /**
     * @return The current value of the Offset dimmer
     */
    qreal offset() const;

    /**
     * set the value of the Offset dimmer
     */
    void setOffset(qreal value);

    /**
     * @return The current wave shape selected, by its value on the selector himself
     */
    QString shape();

    /**
     * Set the value of the selector indirectly : setting this value on the selector himself
     */
    void setShape(QString);

    static const qreal SIGNAL_INTENSITY = 5;
    static const qreal F0 = 261.626; // Frequency of the C4.
    static const qreal REPLAY_FREQUENCY = AudioDeviceProvider::OUTPUT_FREQUENCY;

public slots :
    /**
     * Slot, connected to a signal emitted by the selector to inform its value has changed.
     */
    void waveShapeChanged(int);

protected:
    WaveGenerator* m_waveGenerator;
    WaveGeneratorFactory* m_waveGeneratorFactory;

    OutPort* m_out;
    Selector* m_shapeSelector;
    Dimmer* m_kDimmer;
    Dimmer* m_rangeDimmer;
    Dimmer* m_offsetDimmer;

    static const qreal K_MIN = -10;
    static const qreal K_MAX = -5;
    static const qreal K_DEFAULT = -10;

    static const qreal RANGE_MIN = 0.01;
    static const qreal RANGE_MAX = 1;
    static const qreal RANGE_DEFAULT = 0.02;

    static const qreal OFFSET_MIN = -2;
    static const qreal OFFSET_MAX = 2;
    static const qreal OFFSET_DEFAULT = 0;

    static const QString SHAPE_DEFAULT;

private:
    Buffer* m_lfoBuffer;
};

#endif // LFO_H
