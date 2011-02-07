#include "cvco.h"

CVCO::CVCO(SynthProFactory* factory, QObject* parent)
    : VCO(factory, parent)
    , CModule(parent)
{
}

void CVCO::process()
{
    VCO::process();
}
