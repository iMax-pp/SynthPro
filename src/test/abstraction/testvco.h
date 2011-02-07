#ifndef TESTVCO_H
#define TESTVCO_H

#include "abstraction/vco.h"

#include <QtTest/QTest>

class TestVCO : public QObject {
    Q_OBJECT

private slots:
    void testVCO();
    void testVCOwithDimmer();
};

#endif // TESTVCO_H
