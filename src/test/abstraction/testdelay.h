#ifndef TESTDELAY_H
#define TESTDELAY_H

#include "abstraction/delay.h"

#include <QtTest/QTest>

class TestDelay : public QObject {
    Q_OBJECT

private slots:
    void testDelay();
};

#endif // TESTDELAY_H
