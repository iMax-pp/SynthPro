#include "simplefactory.h"

#include "abstraction/component/connection.h"
#include "abstraction/component/dimmer.h"
#include "abstraction/component/inport.h"
#include "abstraction/component/outport.h"
#include "abstraction/component/pushbutton.h"
#include "abstraction/component/selector.h"
#include "abstraction/module/adsr.h"
#include "abstraction/module/delay.h"
#include "abstraction/module/keyboard.h"
#include "abstraction/module/lfo.h"
#include "abstraction/module/mixer.h"
#include "abstraction/module/oscilloscope.h"
#include "abstraction/module/sampler.h"
#include "abstraction/module/speaker.h"
#include "abstraction/module/vca.h"
#include "abstraction/module/vcf.h"
#include "abstraction/module/vco.h"
#include "abstraction/module/wavlooper.h"
#include "abstraction/module/wavrecorder.h"
#include "abstraction/sequencer.h"
#include "abstraction/synthpro.h"
#include "presentation/module/pwavlooper.h"
#include "presentation/module/pwavrecorder.h"

SynthPro* SimpleFactory::createSynthPro()
{
    return new SynthPro();
}

Connection* SimpleFactory::createConnection(OutPort* source, InPort* target)
{
    return new Connection(source, target);
}

InPort* SimpleFactory::createInPort(Module* parent, const QString& name)
{
    InPort* port = new InPort(parent, name, this, false, false);
    return port;
}

InPort* SimpleFactory::createInPortReplicable(Module* parent, const QString& name)
{
    InPort* port = new InPort(parent, name, this, true, false);
    return port;
}

InPort* SimpleFactory::createInPortGate(Module* parent, const QString& name)
{
    InPort* port = new InPort(parent, name, this, false, true);
    return port;
}

OutPort* SimpleFactory::createOutPort(Module* parent, const QString& name)
{
    OutPort* port = new OutPort(parent, name, this, false, false);
    return port;
}

OutPort* SimpleFactory::createOutPortReplicable(Module* parent, const QString& name)
{
    OutPort* port = new OutPort(parent, name, this, true, false);
    return port;
}

OutPort* SimpleFactory::createOutPortGate(Module* parent, const QString& name)
{
    OutPort* port = new OutPort(parent, name, this, false, true);
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

Delay* SimpleFactory::createDelay(SynthPro* parent)
{
    Delay* delay = new Delay(parent);
    delay->initialize(this);
    return delay;
}

Mixer* SimpleFactory::createMixer(SynthPro* parent)
{
    Mixer* mixer = new Mixer(parent);
    mixer->initialize(this);
    return mixer;
}

LFO* SimpleFactory::createLFO(SynthPro* parent)
{
    LFO* lfo = new LFO(parent);
    lfo->initialize(this);
    return lfo;
}

Sampler* SimpleFactory::createSampler(SynthPro* parent)
{
    Sampler* sampler = new Sampler(parent);
    sampler->initialize(this);
    return sampler;
}

Dimmer* SimpleFactory::createDialDimmer(const QString& /*name*/, qreal min, qreal max, qreal kDefault, Module* parent)
{
    return new Dimmer(min, max, kDefault, parent);
}

Dimmer* SimpleFactory::createSliderDimmer(const QString& /*name*/, qreal min, qreal max, qreal kDefault, Module* parent)
{
    return new Dimmer(min, max, kDefault, parent);
}

Selector* SimpleFactory::createSelector(QList<int> keys, int defaultKey, QList<QString> /*values*/, const QString& /*name*/, Module* parent)
{
    return new Selector(keys, defaultKey, parent);
}


WavRecorder* SimpleFactory::createWavRecorder(SynthPro* parent, int nbProcessingBeforeSaving)
{
    WavRecorder* mbr = new WavRecorder(parent, nbProcessingBeforeSaving);
    mbr->initialize(this);
    return mbr;
}

WavLooper* SimpleFactory::createWavLooper(SynthPro* parent)
{
    WavLooper* wl = new WavLooper(parent);
    wl->initialize(this);
    return wl;
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

Oscilloscope* SimpleFactory::createOscilloscope(SynthPro* synthPro)
{
    return new Oscilloscope(synthPro);
}

Keyboard* SimpleFactory::createKeyboard(SynthPro* synthpro)
{
    Keyboard* keyboard =  new Keyboard(synthpro);
    keyboard->initialize(this);
    return keyboard;
}

PushButton* SimpleFactory::createPushButton(const QString&, Module *parent)
{
    return new PushButton(parent);
}
