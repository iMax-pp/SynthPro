#ifndef TESTADSR_H
#define TESTADSR_H

#include "abstraction/adsr.h"

#include <QtTest/QTest>

class TestADSR : public QObject {
    Q_OBJECT

private slots:
    void testADSR();
};

#endif // TESTADSR_H
