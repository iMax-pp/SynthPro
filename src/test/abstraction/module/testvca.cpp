#include "testvca.h"

#include "abstraction/component/dimmer.h"
#include "abstraction/component/outport.h"
#include "abstraction/mock/mockserializerwell.h"
#include "abstraction/module/speaker.h"
#include "abstraction/module/vco.h"
#include "abstraction/synthpro.h"
#include "factory/simplefactory.h"

#include <QTextStream>

void TestVCA::testVCA()
{
    QString result;
    QTextStream stream(&result);
    int gainTeste = 2;

    SimpleFactory factory;
    SynthPro* synth = factory.createSynthPro();

    VCO* vco = factory.createVCO(synth);
    vco->setShape("Triangle");
    VCA* vca = factory.createVCA(synth);
    vca->setGain(gainTeste);
    MockSerializerWell output(0, stream, &factory);
    vco->outports().first()->connect(vca->inports().first());


    vca->outports().first()->connect(&output.input);
    vco->process();
    vca->process();
    output.process();
    bool res = true;
    // verify that, after the processing, all the vco outport buffer values are multiplied by the gain in the vca buffer.
    for (int i = 0 ; i < Buffer::DEFAULT_LENGTH ; i++) {
        res &= vca->outports().first()->buffer()->data()[i] == gainTeste*vco->outports().first()->buffer()->data()[i];
    }
    QVERIFY(res);
    delete synth;
}
