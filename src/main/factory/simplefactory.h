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
    Sequencer* createSequencer(SynthPro* parent);
    ModuleBufferRecorder* createModuleBufferRecorder(Module* parent, QString fileName = "output.wav", int nbProcessingBeforeSaving = 5);
    Dimmer* createKDimmer(qreal min, qreal max, qreal kDefault, Module* parent);
};

#endif // SIMPLEFACTORY_H
