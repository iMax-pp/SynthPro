#include "factory/qtfactory.h"

#include <QtGui>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    SynthProFactory *factory = new QtFactory();
    factory->createSynthPro();
    return app.exec();
}
