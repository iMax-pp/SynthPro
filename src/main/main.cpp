#include "abstraction/module/vco.h"
#include "abstraction/synthpro.h"
#include "abstraction/wavegen/wavegeneratordummy.h"
#include "factory/qtfactory.h"

#include <QtGui>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    SynthProFactory* factory = new QtFactory();
    SynthPro* synthpro = factory->createSynthPro();

    VCO* vco = factory->createVCO(synthpro);
    synthpro->add(vco);

    vco->process();

    int result = app.exec();

    delete synthpro;

    return result;
}
