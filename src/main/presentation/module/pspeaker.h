#ifndef PSPEAKER_H
#define PSPEAKER_H

#include "presentation/pmodule.h"

#include <QIcon>

class CSpeaker;
class PPushButton;
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
    PPushButton* m_clippingLight;

    QIcon m_iconClippingLightOn;
    QIcon m_iconClippingLightOff;
};

#endif // PSPEAKER_H
