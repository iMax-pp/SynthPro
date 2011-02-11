#include "abstraction/clock.h"
#include "abstraction/sequencer.h"
#include "abstraction/speaker.h"
#include "abstraction/synthpro.h"
#include "abstraction/vco.h"
#include "abstraction/wavegeneratorsquare.h"
#include "factory/qtfactory.h"
#include "factory/simplefactory.h"

#include <QtGui>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
//    SynthProFactory* factory = new QtFactory();
//    SynthPro* synthpro = factory->createSynthPro();

//    VCO* vco = factory->createVCO();
//    vco->setWaveGenerator(new WaveGeneratorDummy());
//    synthpro->add(vco);

//    vco->process();

    qDebug() << "Starting...";

    Clock& clock = Clock::instance();
    clock.start();

    SynthProFactory* factory = new SimpleFactory();
    SynthPro* synthPro = factory->createSynthPro();

    Speaker* mo = factory->createSpeaker(0);
    VCO* vco = factory->createVCO();
    vco->setShape(WaveGeneratorFactory::SawWave);

    vco->outports().at(0)->connectTo(mo->inports().at(0));

    Sequencer& sequencer = Sequencer::instance();
    synthPro->add(mo);
    synthPro->add(vco);
    sequencer.scheduleModules(synthPro);

    mo->setSoundManagement(true);

    qDebug() << "Waiting...";

    int result = app.exec();

//    delete vco;
//    delete synthpro;

    return result;
}
