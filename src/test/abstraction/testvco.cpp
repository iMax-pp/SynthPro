#include "testvco.h"

#include "abstraction/dimmer.h"
#include "abstraction/mockserializerwell.h"
#include "abstraction/outport.h"
#include "abstraction/selector.h"
#include "abstraction/synthpro.h"
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
    SynthPro* synth = factory.createSynthPro();

    VCO* vco = factory.createVCO(synth);
    MockSerializerWell output(0, stream);

    vco->outports().first()->connectTo(&output.input);

    vco->setShape("Dummy");
    vco->process();
    output.process();

    QVERIFY(result.startsWith(QString::number(VCO::SIGNAL_INTENSITY))); // TODO check that *all* the result is as expected (not only the first value)

    delete synth;
}
void TestVCO::testVCOwithDimmer()
{
    QString result;
    QTextStream stream(&result);

    SimpleFactory factory;
    SynthPro* synth = factory.createSynthPro();

    VCO* vco = factory.createVCO(synth);
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

    delete synth;
}
void TestVCO::testVCOWithSelector()
{
    QString result;
    QTextStream stream(&result);

    SimpleFactory factory;
    SynthPro* synth = factory.createSynthPro();

    VCO* vco = factory.createVCO(synth);
    QVERIFY(vco->shape() == "Saw");

    MockSerializerWell output(0, stream);
    vco->outports().first()->connectTo(&output.input);
    vco->setShape("Sinus");
    vco->process();
    output.process();

    QVERIFY(vco->shape() == "Sinus");

    delete synth;
}
