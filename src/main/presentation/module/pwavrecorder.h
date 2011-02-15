#ifndef PWAVRECORDER_H
#define PWAVRECORDER_H

#include "presentation/pmodule.h"

class CWavRecorder;
class PixmapButtonWidget;
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

signals:
    void newFileClicked();
    void startRecordingClicked();
    void stopRecordingClicked();

private:
    PixmapButtonWidget* m_record;
    PixmapButtonWidget* m_stop;
};

#endif // PWAVRECORDER_H
