#ifndef POSCILLOSCOPE_H
#define POSCILLOSCOPE_H

#include "presentation/pmodule.h"

class Buffer;
class COscilloscope;
class POscilloscopeView;
class PVirtualPort;

class POscilloscope : public PModule {

public:
    POscilloscope(COscilloscope*);

    void initialize(PVirtualPort* input);
    void setVisualizedBuffer(Buffer*);
    void refreshOscilloscopeView();

private:
    POscilloscopeView* m_pOscilloscopeView;
};

#endif // POSCILLOSCOPE_H
