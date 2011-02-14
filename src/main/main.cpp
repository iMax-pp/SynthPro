#include "factory/qtfactory.h"

#include <QtGui>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QtFactory* factory = new QtFactory();
    CSynthPro* synthpro = factory->createSynthPro();

    CVCO* vco = factory->createVCO(synthpro);
    vco->presentation()->setPos(-300, 0);
    // synthpro->add(vco);

    CVCA* vca = factory->createVCA(synthpro);
    vca->presentation()->setPos(0, 0);
    // synthpro->add(vca);

    CADSR* adsr = factory->createADSR(synthpro);
    adsr->presentation()->setPos(-100, 300);
    // synthpro->add(adsr);

    CDelay* delay = factory->createDelay(synthpro);
    delay->presentation()->setPos(250, 0);
    // synthpro->add(delay);

    COscilloscope* oscillo = factory->createOscilloscope(synthpro);
    oscillo->presentation()->setPos(450, 0);
    // synthpro->add(oscillo);

    vco->outports().first()->connect(vca->inports().first()); // VCO -> VCA
    adsr->outports().first()->connect(vca->inports().last()); // ADSR -> VCA
    vca->outports().first()->connect(delay->inports().first()); // VCA -> DELAY
    delay->outports().first()->connect(oscillo->inports().first()); // DELAY -> OSCILLO

    int result = app.exec();

    delete synthpro;

    return result;
}
