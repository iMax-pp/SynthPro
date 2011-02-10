#include "testvca.h"

#include "abstraction/dimmer.h"
#include "abstraction/mockserializerwell.h"
#include "abstraction/moduleout.h"
#include "abstraction/outport.h"
#include "abstraction/vco.h"
#include "factory/simplefactory.h"

#include <QTextStream>

void TestVCA::testVCA()
{
    QString result;
    QTextStream stream(&result);

    SimpleFactory factory;

    VCO* vco = factory.createVCO(0);
    VCA* vca = factory.createVCA(0);
    vca->setGain(2);
    MockSerializerWell output(0, stream);
    vco->outports().first()->connectTo(vca->inports().first());


    vca->outports().first()->connectTo(&output.input);
    vco->process();
    vca->process();
    output.process();
    QVERIFY(result.startsWith("-0.118651"));

    delete vco;
    delete vca;

}
