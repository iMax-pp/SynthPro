#include "simplefactory.h"

#include "abstraction/dimmer.h"
#include "abstraction/inport.h"
#include "abstraction/modulebufferrecorder.h"
#include "abstraction/outport.h"
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
    return new VCO(this);
}

Sequencer* SimpleFactory::createSequencer(SynthPro* parent)
{
    return new Sequencer(parent);
}

Dimmer* SimpleFactory::createKDimmer(qreal min, qreal max, qreal kDefault, Module* parent)
{
    return new Dimmer(min, max, kDefault, parent);
}

ModuleBufferRecorder* SimpleFactory::createModuleBufferRecorder(Module* parent, QString fileName, int nbProcessingBeforeSaving)
{
    return new ModuleBufferRecorder(fileName, nbProcessingBeforeSaving, this, parent);
}
