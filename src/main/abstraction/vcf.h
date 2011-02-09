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
    explicit VCF(QObject* parent = 0);
    virtual ~VCF();

    // Initialize the VCO (creates its ports using the factory)
    virtual void initialize(SynthProFactory*);

    /**
     * Process its job : put a buffer in its outPort
     */
    void ownProcess();

    /**
     * Set the Filter to this VCF.
     * The VCF will then take care of deleting it.
     * @deprecated
     */
    void setFilter(Filter*);

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

public slots :
    /**
    * slot, connected to a signal emitted by the selector to inform his value changed.
    */
    void filterChanged(int);

protected:
    Filter* m_filter;
    FilterFactory* m_filterFactory;

    InPort* m_inPort;
    InPort* m_inCutOffPort;
    OutPort* m_out;
    Selector* m_filterSelector;
    Dimmer* m_rDimmer;

    static const qreal R_MIN = -5;
    static const qreal R_MAX = 5;
    static const qreal R_DEFAULT = 0;
};

#endif // VCF_H
