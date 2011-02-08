#include "abstraction/synthpro.h"
#include "abstraction/vco.h"
#include "abstraction/wavegeneratordummy.h"
#include "factory/qtfactory.h"

#include <QtGui>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    SynthProFactory* factory = new QtFactory();
    SynthPro* synthpro = factory->createSynthPro();

    VCO* vco = factory->createVCO();
    vco->setWaveGenerator(new WaveGeneratorDummy()); // FIXME, use the Selector instead.
    synthpro->add(vco);

    vco->process();

    int result = app.exec();

    delete vco;
    delete synthpro;

    return result;
}
