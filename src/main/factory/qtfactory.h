#ifndef QTFACTORY_H
#define QTFACTORY_H

#include "synthprofactory.h"

class QtFactory : public SynthProFactory {
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

    Sequencer* createSequencer(SynthPro* parent);

    Dimmer* createKDimmer(qreal, qreal, qreal, Module* parent);

protected:
    // Convenient factory method
    InPort* createInPort(Module* parent, bool replicable, bool gate);
    OutPort* createOutPort(Module* parent, bool replicable, bool gate);
};

#endif // QTFACTORY_H
