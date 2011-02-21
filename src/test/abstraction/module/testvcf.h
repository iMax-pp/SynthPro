#ifndef TESTVCF_H
#define TESTVCF_H

#include <QObject>

#include <QtTest/QTest>

/**
  * Test the VCF. To do that, creates a VCO that produces
  * an empty wave, use a Incremental filter, and check the result
  * is conform (bufferOut values == FilterIncrement::INCREMENT_VALUE).
  */
class TestVCF : public QObject {
    Q_OBJECT

private slots:
    void testVCF();
};

#endif // TESTVCF_H
