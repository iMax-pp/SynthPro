#ifndef PWAVRECORDER_H
#define PWAVRECORDER_H

#include "presentation/pmodule.h"

class CWavRecorder;
class PPushButton;
class PVirtualPort;

/**
 * Presentation of WavRecorder.
 */
class PWavRecorder : public PModule {
    Q_OBJECT

public:
    explicit PWavRecorder(CWavRecorder*);

    void initialize(PVirtualPort* in, PPushButton* record, PPushButton* stop);

    /// Open a dialog box asking for a file to save in.
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
