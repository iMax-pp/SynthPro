#ifndef CWAVLOOPER_H
#define CWAVLOOPER_H

#include "abstraction/module/wavlooper.h"
#include "control/cmodule.h"

/**
 * WavLooper control class (PAC by inheritance).
 */
class CWavLooper : public WavLooper, public CModule {
    Q_OBJECT

public:
    explicit CWavLooper(SynthPro*);

    void initialize(SynthProFactory*);

    /// @returns a QString containing the different settings of this Module.
    virtual QString settings() const;

    /// @param settings to set up this Module with.
    virtual void setUpSettings(const QString&);

public slots:
    /**
     * Ask the Presentation to prompt the user to select a File, and give the
     * abstraction the filename.
     */
    void newFile();

private:
    static QString formatSpeed(qreal);
};

#endif // CWAVLOOPER_H
