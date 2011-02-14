#include "factory/qtfactory.h"

#include <QtGui>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QtFactory* factory = new QtFactory();
    CSynthPro* synthpro = factory->createSynthPro();

    CVCO* vco = factory->createVCO(synthpro);
    vco->presentation()->setPos(-300, 0);
    synthpro->add(vco);

    CVCA* vca = factory->createVCA(synthpro);
    vca->presentation()->setPos(0, 0);
    synthpro->add(vca);

    CADSR* adsr = factory->createADSR(synthpro);
    adsr->presentation()->setPos(-100, 300);
    synthpro->add(adsr);

    vco->outports().first()->connect(vca->inports().first()); // VCO -> VCA
    adsr->outports().first()->connect(vca->inports().last()); // ADSR -> VCA

    int result = app.exec();

    delete synthpro;

    return result;
}
