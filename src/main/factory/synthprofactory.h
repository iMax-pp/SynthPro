#ifndef SYNTHPROFACTORY_H
#define SYNTHPROFACTORY_H

#include <QString>
#include <QtGlobal>

class ADSR;
class Delay;
class Dimmer;
class InPort;
class LFO;
class Module;
class ModuleKeyboard;
class Oscilloscope;
class OutPort;
class Port;
class PushButton;
class Selector;
class Sequencer;
class Speaker;
class SynthPro;
class VCA;
class VCF;
class VCO;
class VirtualPort;
class WavRecorder;

class SynthProFactory {
public:
    virtual SynthPro* createSynthPro() = 0;

    virtual Port* createPort(VirtualPort* vPort) = 0;

    virtual InPort* createInPort(Module* parent, const QString& name) = 0;
    virtual InPort* createInPortReplicable(Module* parent, const QString& name) = 0;
    virtual InPort* createInPortGate(Module* parent, const QString& name) = 0;

    virtual OutPort* createOutPort(Module* parent, const QString& name) = 0;
    virtual OutPort* createOutPortReplicable(Module* parent, const QString& name) = 0;
    virtual OutPort* createOutPortGate(Module* parent, const QString& name) = 0;

    virtual VCO* createVCO(SynthPro*) = 0;
    virtual LFO* createLFO(SynthPro*) = 0;
    virtual VCF* createVCF(SynthPro*) = 0;
    virtual VCA* createVCA(SynthPro*) = 0;
    virtual ADSR* createADSR(SynthPro*) = 0;
    virtual Delay* createDelay(SynthPro*) = 0;
    virtual WavRecorder* createWavRecorder(SynthPro*, const QString& fileName = "output.wav", int nbProcessingBeforeSaving = 5) = 0;
    virtual ModuleKeyboard* createModuleKeyboard(SynthPro*) = 0;

    /**
      * Instanciate a Speaker, but ONLY if the audio device isn't already used by another instance.
      * @return Speaker if instanciation successful, 0 if not.
      */
    virtual Speaker* createSpeaker(SynthPro*) = 0;

    virtual Oscilloscope* createOscilloscope(SynthPro*) = 0;

    /*
     * instantiate a dimmer's abstraction
     * @param min min value of the dimer
     * @param max max value
     * @param default_value the value where the dimmer is positionned at creation
     */
    virtual Dimmer* createDimmer(const QString& name, qreal min, qreal man, qreal defaultValue, Module* parent) = 0;
    virtual Selector* createSelector(QList<int> keys, int defaultKey, QList<QString> values, const QString& name, Module* parent) = 0;
    virtual PushButton* createPushButton(const QString& name, Module* parent) = 0;

    /*
     * Enumeration of module types.
     */
    enum ModuleType {
        KeyboardId,
        VCOId,
        VCFId,
        VCAId,
        ADSRId,
        LFOId,
        AudioOuputId,
        FileOutputId,
        OscilloscopeId
    };
};

#endif // SYNTHPROFACTORY_H
