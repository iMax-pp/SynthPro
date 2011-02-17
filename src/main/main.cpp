#include "factory/qtfactory.h"

#include <QtGui>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QtFactory* factory = new QtFactory();

    CSynthPro* synthpro = factory->createSynthPro();
    CVCO* vco = factory->createVCO(synthpro);
    synthpro->add(vco);

    int result = app.exec();

    delete synthpro;

    return result;
}
