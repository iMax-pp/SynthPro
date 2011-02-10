#ifndef POSCILLOSCOPE_H
#define POSCILLOSCOPE_H

#include "presentation/pmodule.h"

class COscilloscope;
class PPort;

class POscilloscope : public PModule {
public:
    POscilloscope(COscilloscope*);

    void initialize(PPort* input);
};

#endif // POSCILLOSCOPE_H
