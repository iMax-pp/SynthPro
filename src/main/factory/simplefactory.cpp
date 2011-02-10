#include "simplefactory.h"

#include "abstraction/dimmer.h"
#include "abstraction/inport.h"
#include "abstraction/modulebufferrecorder.h"
#include "abstraction/moduleout.h"
#include "abstraction/outport.h"
#include "abstraction/selector.h"
#include "abstraction/sequencer.h"
#include "abstraction/synthpro.h"
#include "abstraction/vca.h"
#include "abstraction/vcf.h"
#include "abstraction/vco.h"


SynthPro* SimpleFactory::createSynthPro()
{
    return new SynthPro();
}

InPort* SimpleFactory::createInPort(Module* parent, const QString& name)
{
    return new InPort(parent, name, false, false);
}

InPort* SimpleFactory::createInPortReplicable(Module* parent, const QString& name)
{
    return new InPort(parent, name, true, false);
}

InPort* SimpleFactory::createInPortGate(Module* parent, const QString& name)
{
    return new InPort(parent, name, false, true);
}

OutPort* SimpleFactory::createOutPort(Module* parent, const QString& name)
{
    return new OutPort(parent, name, false, false);
}

OutPort* SimpleFactory::createOutPortReplicable(Module* parent, const QString& name)
{
    return new OutPort(parent, name, true, false);
}

OutPort* SimpleFactory::createOutPortGate(Module* parent, const QString& name)
{
    return new OutPort(parent, name, false, true);
}

VCO* SimpleFactory::createVCO()
{
    VCO* vco = new VCO();
    vco->initialize(this);
    return vco;
}

VCF* SimpleFactory::createVCF()
{
    VCF* vcf = new VCF();
    vcf->initialize(this);
    return vcf;
}

VCA* SimpleFactory::createVCA()
{
    VCA* vca = new VCA();
    vca->initialize(this);
    return vca;
}

Dimmer* SimpleFactory::createDimmer(QString name, qreal min, qreal max, qreal kDefault, Module* parent)
{
    return new Dimmer(min, max, kDefault, parent);
}

Selector* SimpleFactory::createSelector(QList<int> keys, int defaultKey, QList<QString> values, QString name, Module* parent)
{
    return new Selector(keys, defaultKey, parent);
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
