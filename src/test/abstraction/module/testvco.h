#ifndef TESTVCO_H
#define TESTVCO_H

#include "abstraction/module/vco.h"

#include <QtTest/QTest>

class TestVCO : public QObject {
    Q_OBJECT

private slots:
    void testVCO();
    void testVCOwithDimmer();
    void testVCOWithSelector();
};

#endif // TESTVCO_H
