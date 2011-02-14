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
    void newFile();
};

#endif // CWAVLOOPER_H
