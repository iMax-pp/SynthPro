#include "testlfo.h"

#include "abstraction/component/dimmer.h"
#include "abstraction/component/outport.h"
#include "abstraction/module/lfo.h"
#include "abstraction/module/vco.h"
#include "abstraction/synthpro.h"
#include "abstraction/wavegen/wavegeneratorsquare.h"
#include "factory/simplefactory.h"

#include <QDebug>

void TestLFO::testLFO()
{
    SimpleFactory factory;

    SynthPro* synthPro = factory.createSynthPro();

    // LFO
    LFO* lfo = factory.createLFO(synthPro);
    lfo->setShape("Square");
    lfo->setK(K);
    lfo->setRange(RANGE);
    lfo->setOffset(OFFSET);

    lfo->process();

    bool result = true;
    qreal* dataOut = lfo->outports().at(0)->buffer()->data();
    int i = 0;
    int size = lfo->outports().at(0)->buffer()->length();
    qreal positiveExpectedValue = VCO::SIGNAL_INTENSITY * RANGE + OFFSET;
    qreal negativeExpectedValue = (VCO::SIGNAL_INTENSITY * -1) * RANGE + OFFSET;
    while (result && (i < size)) {
        result = ((dataOut[i] == positiveExpectedValue) || (dataOut[i] == negativeExpectedValue));
        i++;
    }

    QVERIFY(result);

    delete synthPro;
}
