#ifndef SIMPLEFACTORY_H
#define SIMPLEFACTORY_H

#include "factory/synthprofactory.h"

class SimpleFactory : public SynthProFactory {
public:
    SynthPro* createSynthPro();
    InPort* createInPort(Module* parent, const QString& name);
    InPort* createInPortReplicable(Module* parent, const QString& name);
    InPort* createInPortGate(Module* parent, const QString& name);
    OutPort* createOutPort(Module* parent, const QString& name);
    OutPort* createOutPortReplicable(Module* parent, const QString& name);
    OutPort* createOutPortGate(Module* parent, const QString& name);
    VCO* createVCO();
    ModuleBufferRecorder* createModuleBufferRecorder(Module* parent, QString fileName = "output.wav", int nbProcessingBeforeSaving = 5);
    ModuleOut* createModuleOut(Module* parent);
    Dimmer* createDimmer(qreal min, qreal max, qreal kDefault, Module* parent);
};

#endif // SIMPLEFACTORY_H
