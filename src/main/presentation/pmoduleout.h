#ifndef PMODULEOUT_H
#define PMODULEOUT_H

#include "presentation/pmodule.h"

class CModuleOut;
class PVirtualPort;

class PModuleOut : public PModule {
public:
    PModuleOut(CModuleOut*);

    void initialize(PVirtualPort* in);
};

#endif // PMODULEOUT_H
