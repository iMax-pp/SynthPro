#include "qtfactory.h"

#include "abstraction/audiodeviceprovider.h"
#include "abstraction/modulebufferrecorder.h"
#include "abstraction/moduleout.h"
#include "abstraction/selector.h"
#include "abstraction/sequencer.h"
#include "control/cchannel.h"
#include "control/cdimmer.h"
#include "control/cinport.h"
#include "control/cmodule.h"
#include "control/coutport.h"
#include "control/cport.h"
#include "control/csynthpro.h"
#include "control/cvco.h"
#include "presentation/pchannel.h"
#include "presentation/pdimmer.h"
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

InPort* QtFactory::createInPort(Module* parent, const QString& name, bool replicable, bool gate)
{
    CModule* cParent = dynamic_cast<CModule*>(parent);
    qDebug(QString("QtFactory::createInPort cParent = %1, parent = %2").arg((long)cParent).arg((long)parent).toAscii());
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
    qDebug(QString("QtFactory::createOutPort cParent = %1, parent = %2").arg((long)cParent).arg((long)parent).toAscii());
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

Dimmer* QtFactory::createDimmer(qreal min, qreal max, qreal kDefault, Module* parent)
{
    CModule* cParent = dynamic_cast<CModule*>(parent);
    CDimmer* dimmer = new CDimmer(min, max, kDefault, CDimmer::DISCR, cParent);

    PDimmer* presentation = new PDimmer(dimmer->min() * CDimmer::DISCR,
                                        dimmer->max() * CDimmer::DISCR,
                                        dimmer->value() * CDimmer::DISCR,
                                        cParent->presentation());
    dimmer->setPresentation(presentation);

    return dimmer;
}

Selector* QtFactory::createSelector(QList<int>* valuesList, int defaultValue, Module* parent)
{
    return new Selector(valuesList, defaultValue, parent);
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

    ModuleOut* mo = new ModuleOut(device, adp.audioOutput(), parent);
    mo->initialize(this);
    return mo;
}

CChannel* QtFactory::createChannel(QGraphicsScene* scene)
{
    CChannel* channel = new CChannel();
    PChannel* presentation = new PChannel(channel, scene);
    channel->setPresentation(presentation);

    return channel;
}
