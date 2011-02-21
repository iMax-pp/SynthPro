#ifndef QTFACTORY_H
#define QTFACTORY_H

#include "control/component/cdimmer.h"
#include "control/component/cinport.h"
#include "control/component/coutport.h"
#include "control/component/cport.h"
#include "control/component/cpushbutton.h"
#include "control/component/cselector.h"
#include "control/csynthpro.h"
#include "control/module/cadsr.h"
#include "control/module/cdelay.h"
#include "control/module/ckeyboard.h"
#include "control/module/clfo.h"
#include "control/module/cmixer.h"
#include "control/module/coscilloscope.h"
#include "control/module/csampler.h"
#include "control/module/cspeaker.h"
#include "control/module/cvca.h"
#include "control/module/cvcf.h"
#include "control/module/cvco.h"
#include "control/module/cwavlooper.h"
#include "control/module/cwavrecorder.h"
#include "factory/synthprofactory.h"

class CPortWidget;
class CWire;
class QGraphicsScene;

class QtFactory : public SynthProFactory {
public:
    CSynthPro* createSynthPro();

    Connection* createConnection(OutPort* source, InPort* target);

    CInPort* createInPort(Module* parent, const QString& name);
    CInPort* createInPortReplicable(Module* parent, const QString& name);
    CInPort* createInPortGate(Module* parent, const QString& name);

    COutPort* createOutPort(Module* parent, const QString& name);
    COutPort* createOutPortReplicable(Module* parent, const QString& name);
    COutPort* createOutPortGate(Module* parent, const QString& name);

    CVCO* createVCO(SynthPro*);
    CLFO* createLFO(SynthPro*);
    CKeyboard* createKeyboard(SynthPro*);

    CVCF* createVCF(SynthPro*);
    CVCA* createVCA(SynthPro*);
    CADSR* createADSR(SynthPro*);
    CDelay* createDelay(SynthPro*);
    CMixer* createMixer(SynthPro*);
    CSampler* createSampler(SynthPro*);

    COscilloscope* createOscilloscope(SynthPro*);
    CWavRecorder* createWavRecorder(SynthPro*, bool loadFile = false, int nbProcessingBeforeSaving = 0);
    CWavLooper* createWavLooper(SynthPro*, bool loadFile = false);
    CSpeaker* createSpeaker(SynthPro*);

    CDimmer* createDialDimmer(const QString& name, qreal min, qreal max, qreal defaultValue, Module* parent);
    CDimmer* createSliderDimmer(const QString& name, qreal min, qreal max, qreal defaultValue, Module* parent);
    CSelector* createSelector(QList<int> keys, int defaultKey, QList<QString> values, const QString& name, Module* parent);
    CPushButton* createPushButton(const QString& name, Module* parent);

    // Creation methods specific to the QtFactory
    CPort* createPort(VirtualPort* vPort);
    CWire* createWire(QGraphicsScene*);

protected:
    // Convenient factory method
    CInPort* createInPort(Module* parent, const QString& name, bool replicable, bool gate);
    COutPort* createOutPort(Module* parent, const QString& name, bool replicable, bool gate);
};

#endif // QTFACTORY_H
