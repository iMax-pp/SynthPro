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

    int result = app.exec();

    delete synthpro;

    return result;
}
