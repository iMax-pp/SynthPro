#ifndef SYNTHPROFACTORY_H
#define SYNTHPROFACTORY_H

class InPort;
class Module;
class OutPort;
class Sequencer;
class SynthPro;
class VCO;
class ModuleBufferRecorder;

#include <QString>

class SynthProFactory {
public:
    virtual SynthPro* createSynthPro() = 0;
    virtual InPort* createInPort(Module* parent) = 0;
    virtual InPort* createInPortReplicable(Module* parent) = 0;
    virtual InPort* createInPortGate(Module* parent) = 0;
    virtual OutPort* createOutPort(Module* parent) = 0;
    virtual OutPort* createOutPortReplicable(Module* parent) = 0;
    virtual OutPort* createOutPortGate(Module* parent) = 0;
    virtual VCO* createVCO() = 0;
    virtual Sequencer* createSequencer(SynthPro* parent) = 0;
    virtual ModuleBufferRecorder* createModuleBufferRecorder(Module* parent, QString fileName = "output.wav", int nbProcessingBeforeSaving = 5) = 0;
};

#endif // SYNTHPROFACTORY_H
