#include "abstraction/testsequencer.h"

#include "abstraction/mockinoutmodule.h"
#include "abstraction/mockserializerwell.h"
#include "abstraction/mockwell.h"
#include "abstraction/port.h"
#include "abstraction/sequencer.h"
#include "abstraction/synthpro.h"
#include "abstraction/vco.h"
#include "abstraction/virtualport.h"
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
    SimpleFactory factory;

    SynthPro synthpro;
    Sequencer& sequencer = Sequencer::instance();

    MockInOutModule m1(&synthpro, "1", stream, &factory);
    synthpro.add(&m1);

    MockWell m2(&synthpro, "2", stream, &factory);
    synthpro.add(&m2);

    m1.output.connections().first()->connect(m2.input.connections().first()); // m1 −> m2

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
    SimpleFactory factory;

    SynthPro synthpro;
    Sequencer& sequencer = Sequencer::instance();

    MockInOutModule m1(&synthpro, "1", stream, &factory);
    synthpro.add(&m1);

    MockInOutModule m2(&synthpro, "2", stream, &factory);
    synthpro.add(&m2);

    MockWell m3(&synthpro, "3", stream, &factory);
    synthpro.add(&m3);

    m1.output.connections().first()->connect(m2.input.connections().first()); // m1 −> m2
    m2.output.connections().at(0)->connect(m3.input.connections().first()); // m2 −> m3
    m2.output.connections().at(1)->connect(m1.input.connections().first()); // m2 −> m1

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
    SimpleFactory factory;

    SynthPro synthpro;
    Sequencer& sequencer = Sequencer::instance();

    MockInOutModule m1(&synthpro, "1", stream, &factory);
    synthpro.add(&m1);

    MockWell m2(&synthpro, "2", stream, &factory);
    synthpro.add(&m2);

    MockInOutModule m3(&synthpro, "3", stream, &factory);
    synthpro.add(&m3);

    MockWell m4(&synthpro, "4", stream, &factory);
    synthpro.add(&m4);

    m1.output.connections().at(0)->connect(m2.input.connections().first()); // m1 −> m2
    m1.output.connections().at(1)->connect(m3.input.connections().first()); // m1 −> m3
    m3.output.connections().first()->connect(m4.input.connections().first()); // m3 −> m4

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
    SimpleFactory factory;

    SynthPro synthpro;
    Sequencer& sequencer = Sequencer::instance();

    MockInOutModule m1(&synthpro, "1", stream, &factory);
    synthpro.add(&m1);

    MockInOutModule m2(&synthpro, "2", stream, &factory);
    synthpro.add(&m2);

    m1.output.connections().first()->connect(m2.input.connections().first()); // m1 −> m2

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
    SimpleFactory factory;

    SynthPro synthpro;
    Sequencer& sequencer = Sequencer::instance();

    MockInOutModule m1(&synthpro, "1", stream, &factory);
    synthpro.add(&m1);

    MockInOutModule m2(&synthpro, "2", stream, &factory);
    synthpro.add(&m2);

    MockWell m3(&synthpro, "3", stream, &factory);
    synthpro.add(&m3);

    m1.output.connections().first()->connect(m3.input.connections().at(0)); // m1 −> m3
    m2.output.connections().first()->connect(m3.input.connections().at(1)); // m2 −> m3

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

    SynthPro synthpro;
    Sequencer& sequencer = Sequencer::instance();

    VCO* vco = factory.createVCO(&synthpro);
    vco->setShape("Dummy");
    synthpro.add(vco);

    MockSerializerWell output(&synthpro, stream, &factory);
    synthpro.add(&output);

    vco->outports().first()->connections().first()->connect(output.input.connections().first());

    sequencer.scheduleModules(&synthpro);
    sequencer.process();

    QVERIFY(result.startsWith(QString::number(VCO::SIGNAL_INTENSITY)));
}
