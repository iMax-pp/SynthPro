#include "testvco.h"

#include "abstraction/dimmer.h"
#include "abstraction/mockserializerwell.h"
#include "abstraction/vco.h"
#include "abstraction/wavegeneratordummy.h"
#include "abstraction/wavegeneratorsquare.h"
#include "factory/simplefactory.h"

#include <QTextStream>

void TestVCO::testVCO()
{
    QString result;
    QTextStream stream(&result);

    SimpleFactory factory;
    VCO* vco = factory.createVCO();
    MockSerializerWell output(stream);

    vco->outports().first()->connectTo(&output.input);

    vco->setWaveGenerator(new WaveGeneratorDummy);
    vco->process();
    output.process();

    QVERIFY(result.startsWith("20000")); // TODO check that *all* the result is as expected (not only the first value)

    delete vco;
}
void TestVCO::testVCOwithDimmer()
{
    QString result;
    QTextStream stream(&result);

    SimpleFactory factory;
    VCO* vco = factory.createVCO();
    vco->dimmer()->setValue(0);

    MockSerializerWell output(stream);
    vco->outports().first()->connectTo(&output.input);
    vco->setWaveGenerator(new WaveGeneratorSquare);
    vco->process();
    output.process();
    int nbFronts = 0;
    int oldValue = 0;

    Buffer * buffer = vco->outports().first()->buffer();
    for (int i = 0 ; i < buffer->length()  ; i++) {
        if (i == 0) {
            oldValue = buffer->data()[i];
        }
        if (buffer->data()[i]-oldValue != 0) {
            nbFronts++;
        }
        oldValue = buffer->data()[i];
    }
    QVERIFY(nbFronts != 0); // TODO pourquoi ça marche pas !!!!            

    delete vco;
}
