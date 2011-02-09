#include "abstraction/testsequencer.h"

#include "abstraction/mockinoutmodule.h"
#include "abstraction/mockserializerwell.h"
#include "abstraction/mockwell.h"
#include "abstraction/sequencer.h"
#include "abstraction/synthpro.h"
#include "abstraction/vco.h"
#include "abstraction/wavegeneratordummy.h"
#include "factory/simplefactory.h"

#include <QtTest>

/**
 * Test case simulating two modules connected.
 *   m1 > m2
 */
void TestSequencer::testSortTwoModules()
{
    QString result;
    QTextStream stream(&result);

    SynthPro synthpro;
    Sequencer& sequencer = Sequencer::instance();

    MockInOutModule m1("1", stream);
    synthpro.add(&m1);

    MockWell m2("2", stream);
    synthpro.add(&m2);

    m1.output.connectTo(&m2.input); // m1 −> m2

    sequencer.scheduleModules(&synthpro);
    sequencer.process();

    QCOMPARE(result, QString("12"));
}

/**
 *  +−> m1 −> m2 −+−> m3
 *  +−−−−−−−−−−−−−+
 */
void TestSequencer::testSortCyclingModules()
{
    QString result;
    QTextStream stream(&result);

    SynthPro synthpro;
    Sequencer& sequencer = Sequencer::instance();

    MockInOutModule m1("1", stream);
    synthpro.add(&m1);

    MockInOutModule m2("2", stream);
    synthpro.add(&m2);

    MockWell m3("3", stream);
    synthpro.add(&m3);

    m1.output.connectTo(&m2.input); // m1 −> m2
    m2.output.connectTo(&m3.input); // m2 −> m3
    m2.output.connectTo(&m1.input); // m2 −> m1

    sequencer.scheduleModules(&synthpro);
    sequencer.process();

    QCOMPARE(result, QString("123"));
}

/**
 * m1 −+−> m2
 *     +−> m3 −> m4
 */
void TestSequencer::testSortTwoWells()
{
    QString result;
    QTextStream stream(&result);

    SynthPro synthpro;
    Sequencer& sequencer = Sequencer::instance();

    MockInOutModule m1("1", stream);
    synthpro.add(&m1);

    MockWell m2("2", stream);
    synthpro.add(&m2);

    MockInOutModule m3("3", stream);
    synthpro.add(&m3);

    MockWell m4("4", stream);
    synthpro.add(&m4);

    m1.output.connectTo(&m2.input); // m1 −> m2
    m1.output.connectTo(&m3.input); // m1 −> m3
    m3.output.connectTo(&m4.input); // m3 −> m4

    sequencer.scheduleModules(&synthpro);
    sequencer.process();

    QVERIFY(result.startsWith('1'));
    QVERIFY(result.endsWith('4'));
    QCOMPARE(result.length(), 4);
}

/**
 * m1 −> m2
 * (where m2 is not a well)
 */
void TestSequencer::testSortNoWell()
{
    QString result;
    QTextStream stream(&result);

    SynthPro synthpro;
    Sequencer& sequencer = Sequencer::instance();

    MockInOutModule m1("1", stream);
    synthpro.add(&m1);

    MockInOutModule m2("2", stream);
    synthpro.add(&m2);

    m1.output.connectTo(&m2.input); // m1 −> m2

    sequencer.scheduleModules(&synthpro);
    sequencer.process();

    QCOMPARE(result, QString("")); // No processing at all since theres no well!
}

/**
 * m1 −+
 * m2 −+−> m3
 */
void TestSequencer::testSortMixer()
{
    QString result;
    QTextStream stream(&result);

    SynthPro synthpro;
    Sequencer& sequencer = Sequencer::instance();

    MockInOutModule m1("1", stream);
    synthpro.add(&m1);

    MockInOutModule m2("2", stream);
    synthpro.add(&m2);

    MockWell m3("3", stream);
    synthpro.add(&m3);

    m1.output.connectTo(&m3.input); // m1 −> m3
    m2.output.connectTo(&m3.input); // m2 −> m3

    QVERIFY(m3.requirements().contains(&m1));
    QVERIFY(m3.requirements().contains(&m2));

    sequencer.scheduleModules(&synthpro);
    sequencer.process();

    QVERIFY(result.endsWith('3'));
    QCOMPARE(result.length(), 3);
}

/**
 * VCO −> Serializer
 */
void TestSequencer::testVCOAndSerializer()
{
    QString result;
    QTextStream stream(&result);
    SimpleFactory factory;

    SynthPro* synthpro = factory.createSynthPro();
    Sequencer& sequencer = Sequencer::instance();

    VCO* vco = factory.createVCO();
    vco->setShape("DummyWave");
    synthpro->add(vco);

    MockSerializerWell output(stream);
    synthpro->add(&output);

    vco->outports().first()->connectTo(&output.input);

    sequencer.scheduleModules(synthpro);
    sequencer.process();

    QVERIFY(result.startsWith("20000"));

    delete synthpro;
    delete vco;
}
