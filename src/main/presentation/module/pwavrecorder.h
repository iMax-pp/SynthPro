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
    /**
     * Slot used when the Floppy drawing is clicked.
     */
    void floppyClicked();

signals:
    /**
     * Signal indicating the Floppy drawing has been clicked.
     */
    void newFileClicked();
};

#endif // PWAVRECORDER_H
