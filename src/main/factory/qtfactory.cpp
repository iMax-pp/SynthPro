#include "qtfactory.h"

#include "abstraction/dimmer.h"
#include "abstraction/sequencer.h"
#include "control/cinport.h"
#include "control/coutport.h"
#include "control/csynthpro.h"
#include "control/cvco.h"
#include "presentation/pvco.h"

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
    PVCO* p = new PVCO();
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
    // TODO
    return 0;
}

