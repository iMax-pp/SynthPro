#ifndef CSPEAKER_H
#define CSPEAKER_H

#include "abstraction/module/speaker.h"
#include "control/cmodule.h"

/**
 * Speaker control class (PAC by inheritance).
 */
class CSpeaker : public Speaker, public CModule {
public:
    explicit CSpeaker(SynthPro*, QIODevice*, QAudioOutput*);

    void initialize(SynthProFactory*);

    /// @returns a QString containing the different settings of this Module.
    virtual QString settings() const;

    /// @param settings to set up this Module with.
    virtual void setUpSettings(const QString&);
};

#endif // CSPEAKER_H
