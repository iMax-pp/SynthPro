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
    VCO* createVCO(SynthPro*);
    VCF* createVCF(SynthPro*);
    VCA* createVCA(SynthPro*);
    ADSR* createADSR(SynthPro*);
    LFO* createLFO(SynthPro*);
    ModuleBufferRecorder* createModuleBufferRecorder(SynthPro*, QString fileName = "output.wav", int nbProcessingBeforeSaving = 5);
    ModuleOut* createModuleOut(SynthPro*);
    Dimmer* createDimmer(QString name, qreal min, qreal max, qreal kDefault, Module* parent);
    Selector* createSelector(QList<int> keys, int defaultKey, QList<QString> values, QString name, Module* parent);
};

#endif // SIMPLEFACTORY_H
