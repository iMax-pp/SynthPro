#include "testdelay.h"

#include "abstraction/buffer.h"
#include "abstraction/component/inport.h"
#include "abstraction/component/outport.h"
#include "abstraction/component/port.h"
#include "abstraction/module/vco.h"
#include "abstraction/synthpro.h"
#include "factory/simplefactory.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>

void TestDelay::testDelay()
{
    QFile file("out.txt");
       if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
          return;

    // QTextStream out(&file);

    SimpleFactory factory;
    SynthPro* synth = factory.createSynthPro();
    Delay* delay = factory.createDelay(synth);
    VCO* vco = factory.createVCO(synth);
    vco->outports().first()->connections().first()->connect(delay->inports().first()->connections().first());

    vco->setShape("Sinus");
    for (int i = 0 ; i < 11000 ; i++) {
        if (i%10 == 0) {
            qDebug() << "iteration " << i;
        }
        vco->process();
        delay->process();
    }
   /* for (int i = 0 ; i < delay->buffer()->length();i++) {
        out << i << " " << delay->buffer()->data()[i] << "\n";
    }*/
    file.close();
}
