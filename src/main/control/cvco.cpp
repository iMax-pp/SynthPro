#include "cvco.h"

CVCO::CVCO(SynthProFactory* factory, QObject* parent)
    : VCO(factory, parent)
    , CModule(parent)
{
}
