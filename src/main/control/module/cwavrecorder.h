#ifndef CWAVRECORDER_H
#define CWAVRECORDER_H

#include "abstraction/module/wavrecorder.h"
#include "control/cmodule.h"

/**
 * WavRecorder control class (PAC by inheritance).
 */
class CWavRecorder : public WavRecorder, public CModule {
    Q_OBJECT

public:
    /**
     * CWavRecorder as no processing limit by default. We stop writing to file
     * when the user starts a new file, clicks stop or quits the application.
     */
    CWavRecorder(SynthPro*, int nbProcessingBeforeSaving = 0);

    void initialize(SynthProFactory*);

    /// @returns a QString containing the different settings of this Module.
    virtual QString settings() const;

    /// @param settings to set up this Module with.
    virtual void setUpSettings(const QString&);

protected slots:
    /**
     * Ask the Presentation to prompt the user to select a File, and give the
     * abstraction the filename.
     */
    void newFile();
};

#endif // CWAVRECORDER_H
