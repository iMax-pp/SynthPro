#ifndef SIMPLEFACTORY_H
#define SIMPLEFACTORY_H

#include "factory/synthprofactory.h"

class SimpleFactory : public SynthProFactory {
public:
    SynthPro* createSynthPro();
    Port* createPort(VirtualPort *vPort);
    Connection* createConnection(OutPort* source, InPort* target);
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
    Delay* createDelay(SynthPro*);
    Mixer* createMixer(SynthPro *);
    WavRecorder* createWavRecorder(SynthPro*, int nbProcessingBeforeSaving = 5);
    WavLooper* createWavLooper(SynthPro* parent);
    Speaker* createSpeaker(SynthPro*);
    Keyboard* createKeyboard(SynthPro*);
    Dimmer* createDialDimmer(const QString& name, qreal min, qreal max, qreal kDefault, Module* parent);
    Dimmer* createSliderDimmer(const QString& name, qreal min, qreal max, qreal kDefault, Module* parent);
    Selector* createSelector(QList<int> keys, int defaultKey, QList<QString> values, const QString& name, Module* parent);
    Oscilloscope* createOscilloscope(SynthPro*);
    PushButton* createPushButton(const QString& name, Module* parent);

};

#endif // SIMPLEFACTORY_H
