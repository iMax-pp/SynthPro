#ifndef POSCILLOSCOPE_H
#define POSCILLOSCOPE_H

#include "presentation/pmodule.h"

class Buffer;
class COscilloscope;
class POscilloscopeView;
class PPushButton;
class PVirtualPort;
class QTimer;

/**
 * Presentation of Oscilloscope.
 */
class POscilloscope : public PModule {
    Q_OBJECT

public:
    explicit POscilloscope(COscilloscope*);

    void initialize(PVirtualPort* input, PPushButton* stabilizeButton);

    /**
     * Give the Oscilloscope View the buffer to display.
     */
    void setVisualizedBuffer(Buffer*);

    /**
     * Refresh the Oscilloscope View, but only if the Refresh Timer has allowed it.
     */
    void refreshOscilloscopeView();

private slots:
    /**
     * Slot used when the timer of the view has expired, meaning the view must be refreshed.
     */
    void refreshTimerExpired();

private:
    static const int REFRESH_RATE = 70; // Refresh rate of the view in ms.

    POscilloscopeView* m_pOscilloscopeView;
    QTimer* m_refreshTimer;
    bool m_mustRefreshOscilloscopeView;
};

#endif // POSCILLOSCOPE_H
