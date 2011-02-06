#include "testvco.h"

#include "abstraction/mockserializerwell.h"
#include "abstraction/vco.h"
#include "abstraction/wavegeneratordummy.h"
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
