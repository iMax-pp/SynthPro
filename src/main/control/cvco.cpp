#include "cvco.h"

CVCO::CVCO(SynthProFactory* factory, QObject* parent)
    : Module(parent)
    , VCO(factory, parent)
    , CModule(parent)
{
}
