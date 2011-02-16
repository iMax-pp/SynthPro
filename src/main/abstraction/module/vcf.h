#ifndef VCF_H
#define VCF_H

#include "abstraction/module.h"

class InPort;
class OutPort;
class Dimmer;
class Filter;
class Selector;
class FilterFactory;
class SynthProFactory;

class VCF : public virtual Module {
    Q_OBJECT

public:
    explicit VCF(SynthPro*);
    virtual ~VCF();

    // Initialize the VCO (creates its ports using the factory)
    virtual void initialize(SynthProFactory*);

    /**
     * Process its job : put a buffer in its outPort
     */
    void ownProcess();

    /**
    * @return The current value of the dimmer
    */
    qreal resonance() const;

    /**
    * set the value of the dimmer
    */
    void setResonance(qreal value);

    /**
     * @return The current filter selected, by its value on the selector himself
     */
    QString filter();

    /**
     * Set the value of the selector indirectly : setting this value on the selector himself
     */
    void setFilter(QString);

    static const qreal R_MIN = 0;
    static const qreal R_MAX = 1;
    static const qreal R_DEFAULT = 0;

    static const qreal CUT_OFF_MIN = -4000; // In order to reach easily low frequencies.
    static const qreal CUT_OFF_MAX = 4000;
    static const qreal CUT_OFF_DEFAULT = -4000;

protected slots:
    /**
    * slot, connected to a signal emitted by the selector to inform his value changed.
    */
    virtual void filterChanged(int);

protected:
    Filter* m_filter;
    FilterFactory* m_filterFactory;

    InPort* m_inPort;
    InPort* m_inCutOffPort;
    OutPort* m_out;
    Selector* m_filterSelector;
    Dimmer* m_rDimmer;
    Dimmer* m_cutOffDimmer;
};

#endif // VCF_H
