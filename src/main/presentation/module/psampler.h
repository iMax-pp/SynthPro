#ifndef PSAMPLER_H
#define PSAMPLER_H

#include "presentation/pmodule.h"

class CSampler;
class PDimmer;
class PPushButton;
class PVirtualPort;

/**
 * Presentation of Sampler.
 */
class PSampler : public PModule {
    Q_OBJECT

public:
    explicit PSampler(CSampler*);

    void initialize(PVirtualPort* in, PVirtualPort* out, PVirtualPort* gate, PDimmer* bpm,
                    PPushButton* record, PPushButton* stop, PPushButton* play);

signals:
    void valueChanged(int);
    void lengthChanged(int);
};

#endif // PSAMPLER_H
