#ifndef OSCILLOSCOPE_H
#define OSCILLOSCOPE_H

#include "abstraction/module.h"

class InPort;
class PushButton;
class SynthPro;
class SynthProFactory;

/**
 * Class used to show an Oscilloscope from the Input Buffer.
 */
class Oscilloscope : public virtual Module {
    Q_OBJECT

public:
    Oscilloscope(SynthPro*);
    virtual ~Oscilloscope();

    /**
     * Instanciate the ports. Used by the factory.
     */
    virtual void initialize(SynthProFactory*);

    /**
     * Process the input signal.
     */
    virtual void ownProcess();

    bool stabilized();

protected:
    InPort* m_inPort;
    PushButton* m_stabilizeControl;
    bool m_stabilized;

private slots:
    void stabilizedPushed();
};

#endif // OSCILLOSCOPE_H
