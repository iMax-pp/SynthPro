#ifndef QTFACTORY_H
#define QTFACTORY_H

#include "control/cadsr.h"
#include "control/cdelay.h"
#include "control/cdimmer.h"
#include "control/cinport.h"
#include "control/ckeyboard.h"
#include "control/clfo.h"
#include "control/coscilloscope.h"
#include "control/coutport.h"
#include "control/cport.h"
#include "control/cpushbutton.h"
#include "control/cselector.h"
#include "control/cspeaker.h"
#include "control/csynthpro.h"
#include "control/cvca.h"
#include "control/cvcf.h"
#include "control/cvco.h"
#include "control/cwavrecorder.h"
#include "factory/synthprofactory.h"

class CPortWidget;
class CWire;
class QGraphicsScene;

class QtFactory : public SynthProFactory {
public:
    CSynthPro* createSynthPro();

    CPort* createPort(VirtualPort* vPort);

    CInPort* createInPort(Module* parent, const QString& name);
    CInPort* createInPortReplicable(Module* parent, const QString& name);
    CInPort* createInPortGate(Module* parent, const QString& name);

    COutPort* createOutPort(Module* parent, const QString& name);
    COutPort* createOutPortReplicable(Module* parent, const QString& name);
    COutPort* createOutPortGate(Module* parent, const QString& name);

    CVCO* createVCO(SynthPro*);
    CLFO* createLFO(SynthPro*);
    CVCF* createVCF(SynthPro*);
    CVCA* createVCA(SynthPro*);
    CADSR* createADSR(SynthPro*);
    CDelay* createDelay(SynthPro*);

    CWavRecorder* createWavRecorder(SynthPro*, const QString& fileName = "output.wav", int nbProcessingBeforeSaving = 5);
    CKeyboard* createModuleKeyboard(SynthPro*);
    CSpeaker* createSpeaker(SynthPro*);
    COscilloscope* createOscilloscope(SynthPro*);

    CDimmer* createDimmer(const QString& name, qreal min, qreal max, qreal defaultValue, Module* parent);
    CSelector* createSelector(QList<int> keys, int defaultKey, QList<QString> values, const QString& name, Module* parent);
    CPushButton* createPushButton(const QString& name, Module* parent);

    // Creation methods specific to the QtFactory
    CWire* createWire(QGraphicsScene*);

protected:
    // Convenient factory method
    CInPort* createInPort(Module* parent, const QString& name, bool replicable, bool gate);
    COutPort* createOutPort(Module* parent, const QString& name, bool replicable, bool gate);
};

#endif // QTFACTORY_H
