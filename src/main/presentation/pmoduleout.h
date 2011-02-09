#ifndef PMODULEOUT_H
#define PMODULEOUT_H

#include "presentation/pmodule.h"

class CModuleOut;
class PPort;

class PModuleOut : public PModule {
public:
    PModuleOut(CModuleOut*);

    void initialize(PPort* in);
};

#endif // PMODULEOUT_H
