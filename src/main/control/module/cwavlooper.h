#ifndef CWAVLOOPER_H
#define CWAVLOOPER_H

#include "abstraction/module/wavlooper.h"
#include "control/cmodule.h"

class CWavLooper : public WavLooper, public CModule {
    Q_OBJECT

public:
    CWavLooper(SynthPro*);

    void initialize(SynthProFactory*);

public slots:
    /**
     * Ask the Presentation to prompt the user to select a File, and give the abstraction the filename.
     */
    void newFile();
};

#endif // CWAVLOOPER_H
