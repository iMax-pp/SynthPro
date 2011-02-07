#ifndef PVCO_H
#define PVCO_H

#include "pmodule.h"
#include <QGraphicsProxyWidget>

class PVCO : public PModule {
public:
    PVCO();

private:
    QGraphicsProxyWidget* m_waveSelector;
    QGraphicsProxyWidget* m_kSelector;
};

#endif // PVCO_H
