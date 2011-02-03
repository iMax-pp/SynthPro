#include "qtfactory.h"

#include "control/csynthpro.h"

SynthPro* QtFactory::createSynthPro()
{
    CSynthPro* synthpro = new CSynthPro();
    PSynthPro* gui = new PSynthPro();

    synthpro->setPresentation(gui);
    gui->show();

    return synthpro;
}
