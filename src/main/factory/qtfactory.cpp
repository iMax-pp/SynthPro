#include "qtfactory.h"

#include "abstraction/adsr.h"
#include "abstraction/audiodeviceprovider.h"
#include "abstraction/modulebufferrecorder.h"
#include "abstraction/moduleoscilloscope.h"
#include "abstraction/sequencer.h"
#include "control/cadsr.h"
#include "control/cdimmer.h"
#include "control/cinport.h"
#include "control/clfo.h"
#include "control/cmodule.h"
#include "control/cmoduleout.h"
#include "control/coscilloscope.h"
#include "control/coutport.h"
#include "control/cportwidget.h"
#include "control/cselector.h"
#include "control/csynthpro.h"
#include "control/cvca.h"
#include "control/cvcf.h"
#include "control/cvco.h"
#include "control/cvirtualport.h"
#include "control/cwire.h"
#include "presentation/padsr.h"
#include "presentation/plfo.h"
#include "presentation/pmoduleout.h"
#include "presentation/portwidget.h"
#include "presentation/poscilloscope.h"
#include "presentation/pvca.h"
#include "presentation/pvcf.h"
#include "presentation/pvco.h"
#include "presentation/pvirtualport.h"

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

    PVirtualPort* p = new PVirtualPort(port, cParent->presentation());
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

    PVirtualPort* p = new PVirtualPort(port, cParent->presentation());
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

LFO* QtFactory::createLFO(SynthPro* parent)
{
    // Create the LFO
    CLFO* lfo = new CLFO(parent);

    // Create its presentation
    PLFO* p = new PLFO(lfo);
    lfo->setPresentation(p);

    // Initialize it (ports creation)
    lfo->initialize(this);

    return lfo;
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
    // Create the VCA
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
    // Create the ADSR
    CADSR* adsr = new CADSR(parent);

    // Create its presentation
    PADSR* p = new PADSR(adsr);
    adsr->setPresentation(p);

    // Initialize it (ports creation)
    adsr->initialize(this);

    // return vca;
    return adsr;

>>>>>>> 1311a3fcab64057cf97bb9c0d973a7a44ce0409c
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

ModuleOscilloscope* QtFactory::createModuleOscilloscope(SynthPro* parent)
{
    // Create the Oscilloscope Controler
    COscilloscope* co = new COscilloscope(parent);

    // Create its presentation
    POscilloscope* p = new POscilloscope(co);
    co->setPresentation(p);

    // Initialize it (ports creation)
    co->initialize(this);

    return co;
}

CWire* QtFactory::createWire(QGraphicsScene* scene)
{
    CWire* wire = new CWire();

    PWire* presentation = new PWire(wire, scene);
    wire->setPresentation(presentation);

    return wire;
}

CPortWidget* QtFactory::createPortWidget(CVirtualPort* parent, QtFactory* factory)
{
    CPortWidget* cPortWidget = new CPortWidget(parent, factory);

    PortWidget* presentation = new PortWidget(cPortWidget, parent->presentation());
    cPortWidget->setPresentation(presentation);

    return cPortWidget;
}
