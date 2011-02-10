#ifndef QTFACTORY_H
#define QTFACTORY_H

#include "synthprofactory.h"

class CPortWidget;
class CVirtualPort;
class CWire;
class QGraphicsScene;

class QtFactory : public SynthProFactory {
public:
    SynthPro* createSynthPro();

    InPort* createInPort(Module* parent, const QString& name);
    InPort* createInPortReplicable(Module* parent, const QString& name);
    InPort* createInPortGate(Module* parent, const QString& name);

    OutPort* createOutPort(Module* parent, const QString& name);
    OutPort* createOutPortReplicable(Module* parent, const QString& name);
    OutPort* createOutPortGate(Module* parent, const QString& name);

    VCO* createVCO(SynthPro*);
    LFO* createLFO(SynthPro*);
    VCF* createVCF(SynthPro*);
    VCA* createVCA(SynthPro*);
    ADSR* createADSR(SynthPro*);
    ModuleBufferRecorder* createModuleBufferRecorder(SynthPro*, QString fileName = "output.wav", int nbProcessingBeforeSaving = 5);
    ModuleOut* createModuleOut(SynthPro*);

    Dimmer* createDimmer(QString name, qreal min, qreal max, qreal defaultValue, Module* parent);
    Selector* createSelector(QList<int> keys, int defaultKey, QList<QString> values, QString name, Module* parent);

    // Creation methods specific to the QtFactory
    CWire* createWire(QGraphicsScene*);
    CPortWidget* createPortWidget(CVirtualPort*, QtFactory*);

protected:
    // Convenient factory method
    InPort* createInPort(Module* parent, const QString& name, bool replicable, bool gate);
    OutPort* createOutPort(Module* parent, const QString& name, bool replicable, bool gate);
};

#endif // QTFACTORY_H
