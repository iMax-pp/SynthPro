#ifndef PWAVRECORDER_H
#define PWAVRECORDER_H

#include "presentation/pmodule.h"

class CWavRecorder;
class PPushButton;
class PVirtualPort;

class PWavRecorder : public PModule {
    Q_OBJECT

public:
    explicit PWavRecorder(CWavRecorder*);

    void initialize(PVirtualPort* in, PPushButton* record, PPushButton* stop);
    QString askForFileName();

private slots:
    void floppyClicked();

signals:
    void newFileClicked();
};

#endif // PWAVRECORDER_H
