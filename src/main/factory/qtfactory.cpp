#include "qtfactory.h"

#include "abstraction/audiodeviceprovider.h"
#include "abstraction/modulebufferrecorder.h"
#include "abstraction/selector.h"
#include "abstraction/sequencer.h"
#include "control/cdimmer.h"
#include "control/cinport.h"
#include "control/cmodule.h"
#include "control/cmoduleout.h"
#include "control/coutport.h"
#include "control/cport.h"
#include "control/cselector.h"
#include "control/csynthpro.h"
#include "control/cvca.h"
#include "control/cvcf.h"
#include "control/cvco.h"
#include "control/cwire.h"
#include "presentation/pmoduleout.h"
#include "presentation/pvca.h"
#include "presentation/pvcf.h"
#include "presentation/pvco.h"

#include <QDebug>
#include <QIODevice>

SynthPro* QtFactory::createSynthPro()
{
    CSynthPro* synthpro = new CSynthPro(this);

    PSynthPro* gui = new PSynthPro(synthpro);
    synthpro->setPresentation(gui);
    gui->show();

    return synthpro;
}

InPort* QtFactory::createInPort(Module* parent, const QString& name, bool replicable, bool gate)
{
    CModule* cParent = dynamic_cast<CModule*>(parent);
    qDebug() << "QtFactory::createInPort cParent =" << (long)cParent << ", parent =" << (long)parent;
    CInPort* port = new CInPort(cParent, this, name, replicable, gate);

    PPort* p = new PPort(port, cParent->presentation());
    port->setPresentation(p);

    return port;
}

InPort* QtFactory::createInPort(Module* parent, const QString& name)
{
    return createInPort(parent, name, false, false);
}

InPort* QtFactory::createInPortReplicable(Module* parent, const QString& name)
{
    return createInPort(parent, name, true, false);
}

InPort* QtFactory::createInPortGate(Module* parent, const QString& name)
{
    return createInPort(parent, name, false, true);
}

OutPort* QtFactory::createOutPort(Module* parent, const QString& name, bool replicable, bool gate)
{
    CModule* cParent = dynamic_cast<CModule*>(parent);
    qDebug() << "QtFactory::createOutPort cParent =" << (long)cParent << ", parent =" << (long)parent;
    COutPort* port = new COutPort(cParent, this, name, replicable, gate);

    PPort* p = new PPort(port, cParent->presentation());
    port->setPresentation(p);

    return port;
}

OutPort* QtFactory::createOutPort(Module* parent, const QString& name)
{
    return createOutPort(parent, name, false, false);
}

OutPort* QtFactory::createOutPortReplicable(Module* parent, const QString& name)
{
    return createOutPort(parent, name, true, false);
}

OutPort* QtFactory::createOutPortGate(Module* parent, const QString& name)
{
    return createOutPort(parent, name, false, true);
}

VCO* QtFactory::createVCO()
{
    // Create the VCO
    CVCO* vco = new CVCO();

    // Create its presentation
    PVCO* p = new PVCO(vco);
    vco->setPresentation(p);

    // Initialize it (ports creation)
    vco->initialize(this);

    return vco;
}

VCF* QtFactory::createVCF()
{
    // Create the VCF
    CVCF* vcf = new CVCF();

    // Create its presentation
    PVCF* p = new PVCF(vcf);
    vcf->setPresentation(p);

    // Initialize it (ports creation)
    vcf->initialize(this);

    // return vco;
    return vcf;
}

VCA* QtFactory::createVCA()
{
    // Create the VCO
    CVCA* vca = new CVCA();

    // Create its presentation
    PVCA* p = new PVCA(vca);
    vca->setPresentation(p);

    // Initialize it (ports creation)
    vca->initialize(this);

    // return vca;
    return vca;
}
Dimmer* QtFactory::createDimmer(QString name, qreal min, qreal max, qreal kDefault, Module* parent)
{
    CModule* cParent = dynamic_cast<CModule*>(parent);
    CDimmer* dimmer = new CDimmer(min, max, kDefault, CDimmer::DISCR, cParent);

    PDimmer* presentation = new PDimmer(name, dimmer->min() * CDimmer::DISCR,
                                        dimmer->max() * CDimmer::DISCR,
                                        dimmer->value() * CDimmer::DISCR,
                                        cParent->presentation());
    dimmer->setPresentation(presentation);

    return dimmer;
}

Selector* QtFactory::createSelector(QList<int> keys, int defaultKey, QList<QString> values, QString name, Module* parent)
{
    CModule* cParent = dynamic_cast<CModule*>(parent);
    CSelector* selector = new CSelector(keys, defaultKey, cParent);
    PSelector* presentation = new PSelector(values, name, cParent->presentation());
    selector->setPresentation(presentation);

    return selector;
}

ModuleBufferRecorder* QtFactory::createModuleBufferRecorder(Module* parent, QString fileName, int nbProcessingBeforeSaving)
{
    ModuleBufferRecorder* mbr = new ModuleBufferRecorder(fileName, nbProcessingBeforeSaving, parent);
    mbr->initialize(this);
    return mbr;
}

ModuleOut* QtFactory::createModuleOut(Module* parent)
{
    // Do not instanciate ModuleOut if no audio device can be accessed !
    AudioDeviceProvider& adp = AudioDeviceProvider::instance();
    if (!adp.initializeAudioOutput()) {
        return 0;
    }

    QIODevice* device = adp.device();
    if (!device) {
        return 0;
    }

    CModuleOut* mo = new CModuleOut(device, adp.audioOutput(), parent);

    PModuleOut* p = new PModuleOut(mo);
    mo->setPresentation(p);

    mo->initialize(this);

    return mo;
}

CWire* QtFactory::createWire(QGraphicsScene* scene)
{
    CWire* wire = new CWire();
    PWire* presentation = new PWire(wire, scene);
    wire->setPresentation(presentation);

    return wire;
}
