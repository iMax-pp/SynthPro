#include "vco.h"

VCO::VCO(QObject* parent)
    : Module(parent)
{
}
void VCO::process(){

}

QList<Module*>::const_iterator VCO::getReguirements() const {
    return 0;
}
