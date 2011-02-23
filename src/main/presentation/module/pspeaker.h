#ifndef PSPEAKER_H
#define PSPEAKER_H

#include "presentation/pmodule.h"

#include <QPixmap>

class CSpeaker;
class PixmapWidget;
class PVirtualPort;

/**
 * Presentation of Speaker.
 */
class PSpeaker : public PModule {
    Q_OBJECT

public:
    explicit PSpeaker(CSpeaker*);

    void initialize(PVirtualPort* in);

public slots:
    /**
     * Slot called whenever the Clipping state has changed. Updates the image.
     */
    void clippingStateChanged(bool);

private:
    PixmapWidget* m_clippingLight;

    QPixmap m_iconClippingLightOn;
    QPixmap m_iconClippingLightOff;
};

#endif // PSPEAKER_H
