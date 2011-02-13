#ifndef PWAVRECORDER_H
#define PWAVRECORDER_H

#include "presentation/pmodule.h"

class CWavRecorder;
class PixmapWidget;
class PVirtualPort;

class PWavRecorder : public PModule {
    Q_OBJECT

public:
    explicit PWavRecorder(CWavRecorder*);

    void initialize(PVirtualPort* in);
    QString askForFileName();

private slots:
    void floppyClicked();
    void recordClicked();
    void stopClicked();
    void closeClicked();

signals:
    void newFileClicked();
    void startRecordingClicked();
    void stopRecordingClicked();
    void closeFileClicked();

private:
    PixmapWidget* m_record;
    PixmapWidget* m_stop;
    PixmapWidget* m_close;
};

#endif // PWAVRECORDER_H
