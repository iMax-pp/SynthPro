#ifndef CSYNTHPRO_H
#define CSYNTHPRO_H

#include "abstraction/synthpro.h"
#include "factory/qtfactory.h"
#include "presentation/psynthpro.h"

class QGraphicsScene;

class CSynthPro : public SynthPro {
public:
    CSynthPro();
    virtual ~CSynthPro();

    void setPresentation(PSynthPro*);
    PSynthPro* presentation() const;

    void add(Module*);
    void addModule(QtFactory::ModuleType, QPoint);

private:
    PSynthPro* m_presentation;
    QGraphicsScene* m_graphicsScene;
};

#endif // CSYNTHPRO_H
