#ifndef POSCILLOSCOPE_H
#define POSCILLOSCOPE_H

#include "presentation/pmodule.h"

class COscilloscope;
class PVirtualPort;

class POscilloscope : public PModule {
public:
    POscilloscope(COscilloscope*);

    void initialize(PVirtualPort* input);
};

#endif // POSCILLOSCOPE_H
