#include "cvco.h"

CVCO::CVCO(QObject* parent)
    : Module(parent)
    , VCO(parent)
    , CModule(parent)
{
}
