#include "testvco.h"

#include "abstraction/component/dimmer.h"
#include "abstraction/component/outport.h"
#include "abstraction/component/selector.h"
#include "abstraction/mock/mockserializerwell.h"
#include "abstraction/module/vco.h"
#include "abstraction/synthpro.h"
#include "abstraction/wavegen/wavegeneratordummy.h"
#include "abstraction/wavegen/wavegeneratorsquare.h"
#include "factory/simplefactory.h"

#include <QList>
#include <QSet>
#include <QTextStream>


void TestVCO::testVCO()
{
    QString result;
    QTextStream stream(&result);
    SimpleFactory factory;

    SynthPro* synth = factory.createSynthPro();

    VCO* vco = factory.createVCO(synth);
    MockSerializerWell output(0, stream, &factory);

    vco->outports().first()->connect(&output.input);
    // Dummy is a square wave
    vco->setShape("Dummy");
    vco->process();
    output.process();
    QSet<int> set;
    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; i++) {
        set.insert(output.inports().first()->buffer()->data()[i]);
    }

    QList<int> list = set.toList();
    // Verify that the QSet has two elements and that they are opposites.
    QVERIFY(set.size() == 2);
    QVERIFY(list.at(0) + list.at(1) == 0);

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
    MockSerializerWell output(0, stream, &factory);
    vco->outports().first()->connect(&output.input);
    vco->setShape("Square");
    vco->process();
    output.process();
    int nbFrontsKEgal3 = 0;
    int oldValue = 0;
    // Calcul de nombre de fronts rencontrés dans le buffer avec k = 3
    Buffer* buffer = vco->outports().first()->buffer();

    for (int i = 0 ; i < buffer->length()  ; i++) {
        if (i == 0) {
            oldValue = buffer->data()[i];
        }

        if (buffer->data()[i] - oldValue != 0) {
            nbFrontsKEgal3++;
        }

        oldValue = buffer->data()[i];
    }
    vco->setK(4);
    vco->process();
    output.process();
    int nbFrontsKEgal4 = 0;
    // Calcul de nombre de fronts rencontrés dans le buffer avec k = 4
    for (int i = 0 ; i < buffer->length()  ; i++) {
        if (i == 0) {
            oldValue = buffer->data()[i];
        }

        if (buffer->data()[i] - oldValue != 0) {
            nbFrontsKEgal4++;
        }

        oldValue = buffer->data()[i];
    }

    // vérification que l'on a un fréquence deux fois plus élevée avec k=4 qu'avec k=3 (avec une marge de 2).
    QVERIFY(nbFrontsKEgal4 - 2*nbFrontsKEgal3 < 2);

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

    MockSerializerWell output(0, stream, &factory);
    vco->outports().first()->connect(&output.input);
    vco->setShape("Sinus");
    vco->process();
    output.process();

    QVERIFY(vco->shape() == "Sinus");

    delete synth;
}
