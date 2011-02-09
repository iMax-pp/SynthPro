#ifndef SYNTHPROFACTORY_H
#define SYNTHPROFACTORY_H

#include <QString>
#include <QtGlobal>

class CWire;
class Dimmer;
class InPort;
class Module;
class ModuleBufferRecorder;
class ModuleOut;
class OutPort;
class Selector;
class Sequencer;
class SynthPro;
class QGraphicsScene;
class VCF;
class VCO;
class VCA;


class SynthProFactory {
public:
    virtual SynthPro* createSynthPro() = 0;

    virtual InPort* createInPort(Module* parent, const QString& name) = 0;
    virtual InPort* createInPortReplicable(Module* parent, const QString& name) = 0;
    virtual InPort* createInPortGate(Module* parent, const QString& name) = 0;

    virtual OutPort* createOutPort(Module* parent, const QString& name) = 0;
    virtual OutPort* createOutPortReplicable(Module* parent, const QString& name) = 0;
    virtual OutPort* createOutPortGate(Module* parent, const QString& name) = 0;

    virtual VCO* createVCO() = 0;
    virtual VCF* createVCF() = 0;
    virtual VCA* createVCA() = 0;
    virtual ModuleBufferRecorder* createModuleBufferRecorder(Module* parent, QString fileName = "output.wav", int nbProcessingBeforeSaving = 5) = 0;
    /**
      * Instanciate a ModuleOut, but ONLY if the audio device isn't already used by another instance.
      * @return ModuleOut if instanciation successful, 0 if not.
      */
    virtual ModuleOut* createModuleOut(Module* parent) = 0;

    /*
     * instantiate a dimmer's abstraction
     * @param min min value of the dimer
     * @param max max value
     * @param default_value the value where the dimmer is positionned at creation
     */
    virtual Dimmer* createDimmer(qreal min, qreal man, qreal default_value, Module* parent) = 0;
    virtual Selector* createSelector(QList<int> keys, int defaultKey, QList<QString> values, QString name, Module* parent) = 0;

    virtual CWire* createWire(QGraphicsScene*) = 0;

    /*
     * Enumeration of module types.
     */
    enum ModuleType {
        KeyboardId,
        VCOId,
        VCFId,
        VCAId,
        ADSRId,
        AudioOuputId,
        FileOutputId
    };
};

#endif // SYNTHPROFACTORY_H
