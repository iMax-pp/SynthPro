#ifndef QTFACTORY_H
#define QTFACTORY_H

#include "control/cdimmer.h"
#include "control/cinport.h"
#include "control/clfo.h"
#include "control/cmoduleout.h"
#include "control/coutport.h"
#include "control/cselector.h"
#include "control/csynthpro.h"
#include "control/cvca.h"
#include "control/cvcf.h"
#include "control/cvco.h"
#include "factory/synthprofactory.h"

class CPortWidget;
class CWire;
class QGraphicsScene;

class QtFactory : public SynthProFactory {
public:
    CSynthPro* createSynthPro();

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
    ModuleBufferRecorder* createModuleBufferRecorder(SynthPro*, QString fileName = "output.wav", int nbProcessingBeforeSaving = 5);
    CModuleOut* createModuleOut(SynthPro*);

    CDimmer* createDimmer(QString name, qreal min, qreal max, qreal defaultValue, Module* parent);
    CSelector* createSelector(QList<int> keys, int defaultKey, QList<QString> values, QString name, Module* parent);

    // Creation methods specific to the QtFactory
    CWire* createWire(QGraphicsScene*);
    CPortWidget* createPortWidget(CVirtualPort*, QtFactory*);

protected:
    // Convenient factory method
    CInPort* createInPort(Module* parent, const QString& name, bool replicable, bool gate);
    COutPort* createOutPort(Module* parent, const QString& name, bool replicable, bool gate);
};

#endif // QTFACTORY_H
