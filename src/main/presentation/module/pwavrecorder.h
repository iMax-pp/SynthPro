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

signals:
    void askNewFile();
    void startRecording();
    void stopRecording();

private:
    PixmapWidget* m_record;
    PixmapWidget* m_stop;
};

#endif // PWAVRECORDER_H
