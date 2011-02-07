#ifndef CSYNTHPRO_H
#define CSYNTHPRO_H

#include "abstraction/synthpro.h"
#include "factory/qtfactory.h"
#include "presentation/psynthpro.h"

class QGraphicsScene;

class CSynthPro : public SynthPro {
public:
    CSynthPro(SynthProFactory*);
    virtual ~CSynthPro();

    void setPresentation(PSynthPro*);
    PSynthPro* presentation() const;

    void add(Module*);
    void addModule(QtFactory::ModuleType, const QPointF&);

private:
    PSynthPro* m_presentation;
    QGraphicsScene* m_graphicsScene;
    SynthProFactory* m_factory;
};

#endif // CSYNTHPRO_H
