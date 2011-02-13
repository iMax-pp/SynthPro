#ifndef PVCA_H
#define PVCA_H

#include "presentation/pmodule.h"

class CVCA;
class PDimmer;
class PVirtualPort;

class PVCA : public PModule {
public:
    PVCA(CVCA*);

    void initialize(PVirtualPort* in, PVirtualPort* out, PVirtualPort* controlIn, PDimmer*);
};

#endif // PVCA_H
