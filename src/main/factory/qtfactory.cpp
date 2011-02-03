#include "qtfactory.h"
#include "../control/csynthpro.h"

SynthPro *QtFactory::createSynthPro() {
    return new CSynthPro();
}
