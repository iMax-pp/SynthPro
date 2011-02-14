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

    SimpleFactory factory;
    SynthPro* synth = factory.createSynthPro();

    VCO* vco = factory.createVCO(synth);
    VCA* vca = factory.createVCA(synth);
    vca->setGain(2);
    MockSerializerWell output(0, stream, &factory);
    vco->outports().first()->connect(vca->inports().first());


    vca->outports().first()->connect(&output.input);
    vco->process();
    vca->process();
    output.process();
    QVERIFY(result.startsWith("-0.118651"));

    delete synth;
}
