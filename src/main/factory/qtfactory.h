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
    Sequencer* createSequencer(SynthPro* parent);
    Dimmer* createKDimmer(qreal, qreal, qreal, Module* parent);
    ModuleBufferRecorder* createModuleBufferRecorder(Module* parent, QString fileName, int nbProcessingBeforeSaving);

};

#endif // QTFACTORY_H
