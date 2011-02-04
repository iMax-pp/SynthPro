#include "abstraction/testsequencer.h"

#include "abstraction/mockinoutmodule.h"
#include "abstraction/mockwell.h"
#include "abstraction/sequencer.h"
#include "abstraction/synthpro.h"

#include <QtTest>

void TestSequencer::testSortTwoModules()
{
    QString result;
    QTextStream stream(&result);

    MockInOutModule m1("1", stream);
    MockWell m2("2", stream);

    m1.output.connectTo(&m2.input);

    SynthPro synthpro;
    synthpro.add(&m1);
    synthpro.add(&m2);

    Sequencer sequencer(&synthpro);

    sequencer.scheduleModules();
    sequencer.process();

    QCOMPARE(result, QString("12"));
}
