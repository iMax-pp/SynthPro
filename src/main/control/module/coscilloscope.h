#ifndef COSCILLOSCOPE_H
#define COSCILLOSCOPE_H

#include "abstraction/module/oscilloscope.h"
#include "control/cmodule.h"

/**
 * Oscilloscope control class (PAC by inheritance).
 */
class COscilloscope : public Oscilloscope, public CModule {
public:
    explicit COscilloscope(SynthPro*);

    void initialize(SynthProFactory*);

    /**
     * Order the Presentation it has to refresh itself.
     */
    virtual void ownProcess();

    /// @returns a QString containing the different settings of this Module.
    virtual QString settings() const;

    /// @param settings to set up this Module with.
    virtual void setUpSettings(const QString&);
};

#endif // COSCILLOSCOPE_H
