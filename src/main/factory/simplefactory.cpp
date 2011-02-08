#include "simplefactory.h"

#include "abstraction/dimmer.h"
#include "abstraction/inport.h"
#include "abstraction/modulebufferrecorder.h"
#include "abstraction/moduleout.h"
#include "abstraction/outport.h"
#include "abstraction/selector.h"
#include "abstraction/sequencer.h"
#include "abstraction/synthpro.h"
#include "abstraction/vco.h"

SynthPro* SimpleFactory::createSynthPro()
{
    return new SynthPro();
}

InPort* SimpleFactory::createInPort(Module* parent)
{
    return new InPort(parent, false, false);
}

InPort* SimpleFactory::createInPortReplicable(Module* parent)
{
    return new InPort(parent, true, false);
}

InPort* SimpleFactory::createInPortGate(Module* parent)
{
    return new InPort(parent, false, true);
}

OutPort* SimpleFactory::createOutPort(Module* parent)
{
    return new OutPort(parent, false, false);
}

OutPort* SimpleFactory::createOutPortReplicable(Module* parent)
{
    return new OutPort(parent, true, false);
}

OutPort* SimpleFactory::createOutPortGate(Module* parent)
{
    return new OutPort(parent, false, true);
}

VCO* SimpleFactory::createVCO()
{
    VCO* vco = new VCO();
    vco->initialize(this);
    return vco;
}

Dimmer* SimpleFactory::createDimmer(qreal min, qreal max, qreal kDefault, Module* parent)
{
    return new Dimmer(min, max, kDefault, parent);
}

Selector* SimpleFactory::createSelector(QList<int>* valuesList, int defaultValue, Module* parent)
{
    return new Selector(valuesList, defaultValue, parent);
}


ModuleBufferRecorder* SimpleFactory::createModuleBufferRecorder(Module* parent, QString fileName, int nbProcessingBeforeSaving)
{
    ModuleBufferRecorder* mbr = new ModuleBufferRecorder(fileName, nbProcessingBeforeSaving, parent);
    mbr->initialize(this);
    return mbr;
}

ModuleOut* SimpleFactory::createModuleOut(Module* parent)
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
