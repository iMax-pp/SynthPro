#ifndef PWAVRECORDER_H
#define PWAVRECORDER_H

#include "presentation/pmodule.h"

class CWavRecorder;
class PVirtualPort;

class PWavRecorder : public PModule {
    Q_OBJECT

public:
    explicit PWavRecorder(CWavRecorder*);

    void initialize(PVirtualPort* in);
    QString askForFileName();

signals:
    void newFile();
};

#endif // PWAVRECORDER_H
