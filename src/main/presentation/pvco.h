#ifndef PVCO_H
#define PVCO_H

#include "presentation/pdimmer.h"
#include "presentation/pmodule.h"
#include "presentation/pport.h"
#include <QGraphicsProxyWidget>

class CVCO;

class PVCO : public PModule {
public:
    PVCO(CVCO*);

    void initialize(PPort* vfm, PPort* out, PDimmer*);

private:
    QGraphicsProxyWidget* m_waveSelector;
    QGraphicsProxyWidget* m_kSelector;
};

#endif // PVCO_H
