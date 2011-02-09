#ifndef PVCA_H
#define PVCA_H

#include "pmodule.h"

class CVCA;
class PDimmer;
class PPort;

class PVCA : public PModule {
public:
    PVCA(CVCA*);

    void initialize(PPort* in, PPort* out, PPort* controlIn, PDimmer*);
};

#endif // PVCA_H
