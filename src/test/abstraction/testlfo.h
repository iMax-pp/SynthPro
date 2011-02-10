#ifndef TESTLFO_H
#define TESTLFO_H

#include <QtTest/QTest>

/**
  * Test the LFO. To to that, creates a LFO that produces
  * an square wave, use a Range and add an Offset and check the output buffer.
  */
class TestLFO : public QObject {
    Q_OBJECT

private:
    static const qreal K = 0;
    static const qreal RANGE = 2;
    static const qreal OFFSET = 1;

private slots:
    void testLFO();
};

#endif // TESTLFO_H
