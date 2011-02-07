#include "qtfactory.h"

#include "abstraction/audiodeviceprovider.h"
#include "abstraction/dimmer.h"
#include "abstraction/modulebufferrecorder.h"
#include "abstraction/moduleout.h"
#include "abstraction/sequencer.h"
#include "control/cinport.h"
#include "control/coutport.h"
#include "control/csynthpro.h"
#include "control/cvco.h"

#include <QIODevice>

SynthPro* QtFactory::createSynthPro()
{
    CSynthPro* synthpro = new CSynthPro(this);
    PSynthPro* gui = new PSynthPro(synthpro);

    synthpro->setPresentation(gui);
    gui->show();

    return synthpro;
}

InPort* QtFactory::createInPort(Module* parent)
{
    CInPort* port = new CInPort(parent, false, false);
    return port;
}

InPort* QtFactory::createInPortReplicable(Module* parent)
{
    CInPort* port = new CInPort(parent, true, false);
    return port;
}

InPort* QtFactory::createInPortGate(Module* parent)
{
    CInPort* port = new CInPort(parent, false, true);
    return port;
}

OutPort* QtFactory::createOutPort(Module* parent)
{
    COutPort* port = new COutPort(parent, false, false);
    return port;
}

OutPort* QtFactory::createOutPortReplicable(Module* parent)
{
    COutPort* port = new COutPort(parent, true, false);
    return port;
}

OutPort* QtFactory::createOutPortGate(Module* parent)
{
    COutPort* port = new COutPort(parent, false, true);
    return port;
}

VCO* QtFactory::createVCO()
{
    CVCO* vco = new CVCO(this);
    PModule* p = new PModule();
    vco->setPresentation(p);
    return vco;
}

Sequencer* QtFactory::createSequencer(SynthPro* parent)
{
    Sequencer* sequencer = new Sequencer(parent);
    return sequencer;
}

Dimmer* QtFactory::createKDimmer(qreal min, qreal max, qreal kDefault, Module* parent)
{
    return new Dimmer(min, max, kDefault, parent);
}

ModuleBufferRecorder* QtFactory::createModuleBufferRecorder(Module* parent, QString fileName, int nbProcessingBeforeSaving)
{
    ModuleBufferRecorder* mbr = new ModuleBufferRecorder(fileName, nbProcessingBeforeSaving, this, parent);
    mbr->initialize();
    return mbr;
}

ModuleOut* QtFactory::createModuleOut(Module* parent)
{
    // Do not instanciate ModuleOut if no audio device can be accessed !
    AudioDeviceProvider adp = AudioDeviceProvider::instance();
    if (!adp.initializeAudioOutput()) {
        return 0;
    }

    QIODevice* device = adp.device();
    if (!device) {
        return 0;
    }
    return new ModuleOut(device, this, parent);
}
