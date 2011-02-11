#include "simplefactory.h"

#include "abstraction/adsr.h"
#include "abstraction/dimmer.h"
#include "abstraction/inport.h"
#include "abstraction/lfo.h"
#include "abstraction/modulekeyboard.h"
#include "abstraction/moduleoscilloscope.h"
#include "abstraction/outport.h"
#include "abstraction/port.h"
#include "abstraction/pushbutton.h"
#include "abstraction/selector.h"
#include "abstraction/sequencer.h"
#include "abstraction/speaker.h"
#include "abstraction/synthpro.h"
#include "abstraction/vca.h"
#include "abstraction/vcf.h"
#include "abstraction/vco.h"
#include "abstraction/wavrecorder.h"

SynthPro* SimpleFactory::createSynthPro()
{
    return new SynthPro();
}

Port* SimpleFactory::createPort(VirtualPort* vPort)
{
    Port* port = new Port(vPort);
    return port;
}

InPort* SimpleFactory::createInPort(Module* parent, const QString& name)
{
    InPort* port = new InPort(parent, name, this, false, false);
    port->initialize();
    return port;
}

InPort* SimpleFactory::createInPortReplicable(Module* parent, const QString& name)
{
    InPort* port = new InPort(parent, name, this, true, false);
    port->initialize();
    return port;
}

InPort* SimpleFactory::createInPortGate(Module* parent, const QString& name)
{
    InPort* port = new InPort(parent, name, this, false, true);
    port->initialize();
    return port;
}

OutPort* SimpleFactory::createOutPort(Module* parent, const QString& name)
{
    OutPort* port = new OutPort(parent, name, this, false, false);
    port->initialize();
    return port;
}

OutPort* SimpleFactory::createOutPortReplicable(Module* parent, const QString& name)
{
    OutPort* port = new OutPort(parent, name, this, true, false);
    port->initialize();
    return port;
}

OutPort* SimpleFactory::createOutPortGate(Module* parent, const QString& name)
{
    OutPort* port = new OutPort(parent, name, this, false, true);
    port->initialize();
    return port;
}

VCO* SimpleFactory::createVCO(SynthPro* parent)
{
    VCO* vco = new VCO(parent);
    vco->initialize(this);
    return vco;
}

VCF* SimpleFactory::createVCF(SynthPro* parent)
{
    VCF* vcf = new VCF(parent);
    vcf->initialize(this);
    return vcf;
}

VCA* SimpleFactory::createVCA(SynthPro* parent)
{
    VCA* vca = new VCA(parent);
    vca->initialize(this);
    return vca;
}


ADSR* SimpleFactory::createADSR(SynthPro* parent)
{
    ADSR* adsr = new ADSR(parent);
    adsr->initialize(this);
    return adsr;
}

LFO* SimpleFactory::createLFO(SynthPro* parent)
{
    LFO* lfo = new LFO(parent);
    lfo->initialize(this);
    return lfo;
}

Dimmer* SimpleFactory::createDimmer(const QString& name, qreal min, qreal max, qreal kDefault, Module* parent)
{
    return new Dimmer(min, max, kDefault, parent);
}

Selector* SimpleFactory::createSelector(QList<int> keys, int defaultKey, QList<QString> values, const QString& name, Module* parent)
{
    return new Selector(keys, defaultKey, parent);
}


WavRecorder* SimpleFactory::createWavRecorder(SynthPro* parent, const QString& fileName, int nbProcessingBeforeSaving)
{
    WavRecorder* mbr = new WavRecorder(parent, fileName, nbProcessingBeforeSaving);
    mbr->initialize(this);
    return mbr;
}

Speaker* SimpleFactory::createSpeaker(SynthPro* parent)
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

    Speaker* mo = new Speaker(parent, device, adp.audioOutput());
    mo->initialize(this);
    return mo;
}

ModuleOscilloscope* SimpleFactory::createModuleOscilloscope(SynthPro* synthPro)
{
    return new ModuleOscilloscope(synthPro);
}

ModuleKeyboard* SimpleFactory::createModuleKeyboard(SynthPro* synthpro)
{
    return new ModuleKeyboard(synthpro);
}

PushButton* SimpleFactory::createPushButton(const QString&, Module *parent)
{
    return new PushButton(parent);
}
