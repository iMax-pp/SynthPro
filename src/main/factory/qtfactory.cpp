#include "qtfactory.h"

#include "abstraction/vco.h"
#include "control/cinport.h"
#include "control/coutport.h"
#include "control/csynthpro.h"

SynthPro* QtFactory::createSynthPro()
{
    CSynthPro* synthpro = new CSynthPro();
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
    VCO* vco = new VCO();
    return vco;
}
