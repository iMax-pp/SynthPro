#include "testvca.h"

#include "abstraction/dimmer.h"
#include "abstraction/mockserializerwell.h"
#include "abstraction/outport.h"
#include "abstraction/port.h"
#include "abstraction/speaker.h"
#include "abstraction/synthpro.h"
#include "abstraction/vco.h"
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
    vco->outports().first()->connections().first()->connect(vca->inports().first()->connections().first());


    vca->outports().first()->connections().first()->connect(output.input.connections().first());
    vco->process();
    vca->process();
    output.process();
    QVERIFY(result.startsWith("-0.118651"));

    delete synth;
}
