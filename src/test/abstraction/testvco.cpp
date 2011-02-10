#include "testvco.h"

#include "abstraction/dimmer.h"
#include "abstraction/mockserializerwell.h"
#include "abstraction/outport.h"
#include "abstraction/selector.h"
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
    VCO* vco = factory.createVCO(0);
    MockSerializerWell output(0, stream);

    vco->outports().first()->connectTo(&output.input);

    vco->setShape("Dummy");
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
    VCO* vco = factory.createVCO(0);
    vco->setK(3);
    MockSerializerWell output(0, stream);
    vco->outports().first()->connectTo(&output.input);
    vco->setShape("Square");
    vco->process();
    output.process();
    int nbFronts = 0;
    int oldValue = 0;

    Buffer* buffer = vco->outports().first()->buffer();

    for (int i = 0 ; i < buffer->length()  ; i++) {
        if (i == 0) {
            oldValue = buffer->data()[i];
        }

        if (buffer->data()[i] - oldValue != 0) {
            nbFronts++;
        }

        oldValue = buffer->data()[i];
    }

    QVERIFY(nbFronts != 0);

    delete vco;
}
void TestVCO::testVCOWithSelector()
{
    QString result;
    QTextStream stream(&result);

    SimpleFactory factory;
    VCO* vco = factory.createVCO(0);
    QVERIFY(vco->shape() == "Saw");

    MockSerializerWell output(0, stream);
    vco->outports().first()->connectTo(&output.input);
    vco->setShape("Sinus");
    vco->process();
    output.process();

    QVERIFY(vco->shape() == "Sinus");

    delete vco;
}
