#include "qtfactory.h"

#include "abstraction/adsr.h"
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
#include "control/cportwidget.h"
#include "control/cselector.h"
#include "control/csynthpro.h"
#include "control/cvca.h"
#include "control/cvcf.h"
#include "control/cvco.h"
#include "control/cwire.h"
#include "presentation/pmoduleout.h"
#include "presentation/portwidget.h"
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

    port->initialize();

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

    port->initialize();

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

VCO* QtFactory::createVCO(SynthPro* parent)
{
    // Create the VCO
    CVCO* vco = new CVCO(parent);

    // Create its presentation
    PVCO* p = new PVCO(vco);
    vco->setPresentation(p);

    // Initialize it (ports creation)
    vco->initialize(this);

    return vco;
}

VCF* QtFactory::createVCF(SynthPro* parent)
{
    // Create the VCF
    CVCF* vcf = new CVCF(parent);

    // Create its presentation
    PVCF* p = new PVCF(vcf);
    vcf->setPresentation(p);

    // Initialize it (ports creation)
    vcf->initialize(this);

    // return vco;
    return vcf;
}

VCA* QtFactory::createVCA(SynthPro* parent)
{
    // Create the VCO
    CVCA* vca = new CVCA(parent);

    // Create its presentation
    PVCA* p = new PVCA(vca);
    vca->setPresentation(p);

    // Initialize it (ports creation)
    vca->initialize(this);

    // return vca;
    return vca;
}

ADSR* QtFactory::createADSR(SynthPro* parent)
{
    ADSR* adsr = new ADSR(parent);
    adsr->initialize(this);
    return adsr;
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

ModuleBufferRecorder* QtFactory::createModuleBufferRecorder(SynthPro* parent, QString fileName, int nbProcessingBeforeSaving)
{
    ModuleBufferRecorder* mbr = new ModuleBufferRecorder(parent, fileName, nbProcessingBeforeSaving);
    mbr->initialize(this);
    return mbr;
}

ModuleOut* QtFactory::createModuleOut(SynthPro* parent)
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

    CModuleOut* mo = new CModuleOut(parent, device, adp.audioOutput());

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

CPortWidget* QtFactory::createPortWidget(CPort* parent, QtFactory* factory)
{
    CPortWidget* cPortWidget = new CPortWidget(parent, factory);

    PortWidget* presentation = new PortWidget(cPortWidget, parent->presentation());
    cPortWidget->setPresentation(presentation);

    return cPortWidget;
}
