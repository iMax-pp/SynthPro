#ifndef TIMECRITICALMODULE_H
#define TIMECRITICALMODULE_H

#include "abstraction/module.h"

/**
 * Specialized Module especially used by the Clock.
 * Once registered to the Clock, their slot criticalTimerExpired will
 * be called.
 */
class TimeCriticalModule : public virtual /* ajout ! */ Module {
    Q_OBJECT

public:
    explicit TimeCriticalModule(SynthPro*);
    virtual ~TimeCriticalModule();

    /**
     * Method called by the Sequencer. Process the inputs and fill the ouputs.
     */
    virtual void ownProcess() = 0;

signals:

public slots:
    /// Slot used by the Clock only for time-critical operations (like Audio Output).
    virtual void criticalTimerExpired() = 0;

};

#endif // TIMECRITICALMODULE_H
