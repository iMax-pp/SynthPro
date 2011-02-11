#ifndef POSCILLOSCOPE_H
#define POSCILLOSCOPE_H

#include "presentation/pmodule.h"

class COscilloscope;
class POscilloscopeView;
class PVirtualPort;

class POscilloscope : public PModule {
public:
    POscilloscope(COscilloscope*);

    void initialize(PVirtualPort* input);

private:
    POscilloscopeView* m_pOscilloscopeView;
};

#endif // POSCILLOSCOPE_H
