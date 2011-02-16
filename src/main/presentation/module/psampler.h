#ifndef PSAMPLER_H
#define PSAMPLER_H

#include "presentation/pmodule.h"

class CSampler;
class PDimmer;
class PixmapButtonWidget;
class PVirtualPort;

class PSampler : public PModule {
    Q_OBJECT

public:
    explicit PSampler(CSampler*);

    void initialize(PVirtualPort* in, PVirtualPort* out, PVirtualPort* gate, PDimmer* bpm);

private slots:
    void recordClicked();
    void stopClicked();
    void playClicked();

signals:
    void startRecordingClicked();
    void stopRecordingClicked();
    void startPlayingClicked();

private:
    PixmapButtonWidget* m_record;
    PixmapButtonWidget* m_stop;
    PixmapButtonWidget* m_play;
};

#endif // PSAMPLER_H
