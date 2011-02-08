#include "qtfactory.h"

#include "abstraction/audiodeviceprovider.h"
#include "abstraction/dimmer.h"
#include "abstraction/modulebufferrecorder.h"
#include "abstraction/moduleout.h"
#include "abstraction/sequencer.h"
#include "control/cinport.h"
#include "control/cmodule.h"
#include "control/coutport.h"
#include "control/cport.h"
#include "control/csynthpro.h"
#include "control/cvco.h"
#include "presentation/pvco.h"

#include <QIODevice>

SynthPro* QtFactory::createSynthPro()
{
    CSynthPro* synthpro = new CSynthPro(this);

    PSynthPro* gui = new PSynthPro(synthpro);
    synthpro->setPresentation(gui);
    gui->show();

    return synthpro;
}

InPort* QtFactory::createInPort(Module* parent, bool replicable, bool gate)
{
    CModule* cParent = dynamic_cast<CModule*>(parent);
    qDebug(QString("QtFactory::createInPort cParent = %1, parent = %2").arg((long)cParent).arg((long)parent).toAscii());
    CInPort* port = new CInPort(cParent, replicable, gate);

    PPort* p = new PPort(cParent->presentation());
    port->setPresentation(p);

    return port;
}

InPort* QtFactory::createInPort(Module* parent)
{
    return createInPort(parent, false, false);
}

InPort* QtFactory::createInPortReplicable(Module* parent)
{
    return createInPort(parent, true, false);
}

InPort* QtFactory::createInPortGate(Module* parent)
{
    return createInPort(parent, false, true);
}

OutPort* QtFactory::createOutPort(Module* parent, bool replicable, bool gate)
{
    CModule* cParent = dynamic_cast<CModule*>(parent);
    qDebug(QString("QtFactory::createOutPort cParent = %1, parent = %2").arg((long)cParent).arg((long)parent).toAscii());
    COutPort* port = new COutPort(cParent, replicable, gate);

    PPort* p = new PPort(cParent->presentation());
    port->setPresentation(p);

    return port;
}

OutPort* QtFactory::createOutPort(Module* parent)
{
    return createOutPort(parent, false, false);
}

OutPort* QtFactory::createOutPortReplicable(Module* parent)
{
    return createOutPort(parent, true, false);
}

OutPort* QtFactory::createOutPortGate(Module* parent)
{
    return createOutPort(parent, false, true);
}

VCO* QtFactory::createVCO()
{
    // Create the VCO
    CVCO* vco = new CVCO();

    // Create its presentation
    PVCO* p = new PVCO();
    vco->setPresentation(p);

    // Initialize it (ports creation)
    vco->initialize(this);

    return vco;
}

Dimmer* QtFactory::createKDimmer(qreal min, qreal max, qreal kDefault, Module* parent)
{
    return new Dimmer(min, max, kDefault, parent);
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
    return new ModuleOut(device, this, parent);
}
