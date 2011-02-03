#include "abstraction/synthpro.h"
#include "factory/qtfactory.h"

#include <QtGui>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    SynthProFactory* factory = new QtFactory();
    SynthPro* synthpro = factory->createSynthPro();

    int result = app.exec();

    delete synthpro;

    return result;
}
