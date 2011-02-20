#ifndef PWAVLOOPER_H
#define PWAVLOOPER_H

#include "presentation/pmodule.h"

class CWavLooper;
class PDimmer;
class PVirtualPort;

/**
 * Presentation of WavLooper.
 */
class PWavLooper : public PModule {
    Q_OBJECT

public:
    explicit PWavLooper(CWavLooper*);

    void initialize(PVirtualPort* out, PDimmer* speedDimmer);

    /// Open a dialog box asking for a file to open.
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

#endif // PWAVLOOPER_H
