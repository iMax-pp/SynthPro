#ifndef SYNTHPROFACTORY_H
#define SYNTHPROFACTORY_H

#include <QString>
#include <QtGlobal>

class Dimmer;
class InPort;
class Module;
class ModuleBufferRecorder;
class OutPort;
class Sequencer;
class SynthPro;
class VCO;


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
    /*
    * instantiate a dimmer's abstraction
    * @param min min value of the dimer
    * @param max max value
    * @param default_value the value where the dimmer is positionned at creation
    */
    virtual Dimmer* createKDimmer(qreal min, qreal man, qreal default_value, Module* parent) = 0;
    virtual ModuleBufferRecorder* createModuleBufferRecorder(Module* parent, QString fileName = "output.wav", int nbProcessingBeforeSaving = 5) = 0;
};

#endif // SYNTHPROFACTORY_H
