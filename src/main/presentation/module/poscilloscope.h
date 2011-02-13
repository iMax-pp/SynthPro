#ifndef POSCILLOSCOPE_H
#define POSCILLOSCOPE_H

#include "presentation/pmodule.h"

class Buffer;
class COscilloscope;
class POscilloscopeView;
class PVirtualPort;
class QTimer;

class POscilloscope : public PModule {
    Q_OBJECT

public:
    POscilloscope(COscilloscope*);

    void initialize(PVirtualPort* input);
    void setVisualizedBuffer(Buffer*);
    void refreshOscilloscopeView();

private slots:
    void refreshTimerExpired();

private:
    static const int REFRESH_RATE = 60; // Refresh rate of the view in ms.

    POscilloscopeView* m_pOscilloscopeView;
    QTimer* m_refreshTimer;
    bool m_mustRefreshOscilloscopeView;
};

#endif // POSCILLOSCOPE_H
