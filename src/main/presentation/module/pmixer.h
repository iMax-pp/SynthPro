#ifndef PMIXER_H
#define PMIXER_H

#include "presentation/pmodule.h"

#include <QMap>

class CMixer;
class PDimmer;
class PVirtualPort;
class PPort;


class PMixer : public PModule {
public:
    explicit PMixer(CMixer*);

    void initialize(QMap<PVirtualPort*, PDimmer*>*, PVirtualPort*);
};

#endif // PMIXER_H
