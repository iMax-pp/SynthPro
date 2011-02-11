#include "qtfactory.h"

#include "abstraction/adsr.h"
#include "abstraction/audiodeviceprovider.h"
#include "abstraction/moduleoscilloscope.h"
#include "abstraction/port.h"
#include "abstraction/sequencer.h"
#include "abstraction/wavrecorder.h"
#include "control/cwire.h"
#include "presentation/padsr.h"
#include "presentation/pkeyboard.h"
#include "presentation/plfo.h"
#include "presentation/poscilloscope.h"
#include "presentation/pport.h"
#include "presentation/ppushbutton.h"
#include "presentation/pspeaker.h"
#include "presentation/pvca.h"
#include "presentation/pvcf.h"
#include "presentation/pvco.h"
#include "presentation/pvirtualport.h"

#include <QDebug>
#include <QIODevice>

CSynthPro* QtFactory::createSynthPro()
{
    CSynthPro* synthpro = new CSynthPro(this);

    PSynthPro* gui = new PSynthPro(synthpro);
    synthpro->setPresentation(gui);
    gui->show();

    return synthpro;
}

CPort* QtFactory::createPort(VirtualPort* vPort)
{
    CVirtualPort* cVPort = dynamic_cast<CVirtualPort*>(vPort);

    CPort* port = new CPort(cVPort, this);

    PPort* presentation = new PPort(port, cVPort->presentation());
    port->setPresentation(presentation);

    return port;
}

CInPort* QtFactory::createInPort(Module* parent, const QString& name, bool replicable, bool gate)
{
    CModule* cParent = dynamic_cast<CModule*>(parent);
    CInPort* port = new CInPort(cParent, this, name, replicable, gate);

    PVirtualPort* p = new PVirtualPort(port, cParent->presentation());
    port->setPresentation(p);

    port->initialize();

    return port;
}

CInPort* QtFactory::createInPort(Module* parent, const QString& name)
{
    return createInPort(parent, name, false, false);
}

CInPort* QtFactory::createInPortReplicable(Module* parent, const QString& name)
{
    return createInPort(parent, name, true, false);
}

CInPort* QtFactory::createInPortGate(Module* parent, const QString& name)
{
    return createInPort(parent, name, false, true);
}

COutPort* QtFactory::createOutPort(Module* parent, const QString& name, bool replicable, bool gate)
{
    CModule* cParent = dynamic_cast<CModule*>(parent);
    COutPort* port = new COutPort(cParent, this, name, replicable, gate);

    PVirtualPort* p = new PVirtualPort(port, cParent->presentation());
    port->setPresentation(p);

    port->initialize();

    return port;
}

COutPort* QtFactory::createOutPort(Module* parent, const QString& name)
{
    return createOutPort(parent, name, false, false);
}

COutPort* QtFactory::createOutPortReplicable(Module* parent, const QString& name)
{
    return createOutPort(parent, name, true, false);
}

COutPort* QtFactory::createOutPortGate(Module* parent, const QString& name)
{
    return createOutPort(parent, name, false, true);
}

CVCO* QtFactory::createVCO(SynthPro* parent)
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

CLFO* QtFactory::createLFO(SynthPro* parent)
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

CVCF* QtFactory::createVCF(SynthPro* parent)
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

CVCA* QtFactory::createVCA(SynthPro* parent)
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

CADSR* QtFactory::createADSR(SynthPro* parent)
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

}

CDimmer* QtFactory::createDimmer(const QString& name, qreal min, qreal max, qreal kDefault, Module* parent)
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

CSelector* QtFactory::createSelector(QList<int> keys, int defaultKey, QList<QString> values, const QString& name, Module* parent)
{
    CModule* cParent = dynamic_cast<CModule*>(parent);
    CSelector* selector = new CSelector(keys, defaultKey, cParent);
    PSelector* presentation = new PSelector(values, name, cParent->presentation());
    selector->setPresentation(presentation);

    return selector;
}

CPushButton* QtFactory::createPushButton(const QString& name, Module* parent)
{
    CModule* cParent = dynamic_cast<CModule*>(parent);
    CPushButton* pushButton = new CPushButton(cParent);
    PPushButton* presentation = new PPushButton(name, cParent->presentation());
    pushButton->setPresentation(presentation);

    return pushButton;
}

WavRecorder* QtFactory::createWavRecorder(SynthPro* parent, const QString& fileName, int nbProcessingBeforeSaving)
{
    WavRecorder* mbr = new WavRecorder(parent, fileName, nbProcessingBeforeSaving);
    mbr->initialize(this);
    return mbr;
}

CKeyboard* QtFactory::createModuleKeyboard(SynthPro* parent)
{
    // Create the Keyboard Controler
    CKeyboard* ck = new CKeyboard(parent);

    // Create its presentation
    PKeyboard* p = new PKeyboard(ck);
    ck->setPresentation(p);

    // Initialize it (ports creation)
    ck->initialize(this);

    return ck;
}

CSpeaker* QtFactory::createSpeaker(SynthPro* parent)
{
    // Do not instanciate Speaker if no audio device can be accessed !
    AudioDeviceProvider& adp = AudioDeviceProvider::instance();

    if (!adp.initializeAudioOutput()) {
        return 0;
    }

    QIODevice* device = adp.device();

    if (!device) {
        return 0;
    }

    CSpeaker* mo = new CSpeaker(parent, device, adp.audioOutput());

    PSpeaker* p = new PSpeaker(mo);
    mo->setPresentation(p);

    mo->initialize(this);

    return mo;
}

COscilloscope* QtFactory::createModuleOscilloscope(SynthPro* parent)
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
