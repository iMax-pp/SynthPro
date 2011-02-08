#ifndef SIMPLEFACTORY_H
#define SIMPLEFACTORY_H

#include "factory/synthprofactory.h"

class SimpleFactory : public SynthProFactory {
public:
    SynthPro* createSynthPro();
    InPort* createInPort(Module* parent);
    InPort* createInPortReplicable(Module* parent);
    InPort* createInPortGate(Module* parent);
    OutPort* createOutPort(Module* parent);
    OutPort* createOutPortReplicable(Module* parent);
    OutPort* createOutPortGate(Module* parent);
    VCO* createVCO();
    ModuleBufferRecorder* createModuleBufferRecorder(Module* parent, QString fileName = "output.wav", int nbProcessingBeforeSaving = 5);
    ModuleOut* createModuleOut(Module* parent);
<<<<<<< HEAD
    Dimmer* createKDimmer(qreal min, qreal max, qreal kDefault, Module* parent);
    Selector* createSelector(QList<int>* valuesList, int defaultValue, Module* parent);
=======
    Dimmer* createDimmer(qreal min, qreal max, qreal kDefault, Module* parent);
>>>>>>> b36d52d75deb8dd9d3222bf0220a9c649c7c8490
};

#endif // SIMPLEFACTORY_H
